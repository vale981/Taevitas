#include "recorder.h"
using namespace FlyCapture2;

Recorder::Recorder(QObject* parent) : QObject(parent) : frame_n {0}, time_c {0} {
	// Initializing References
	frame_number = frame_n:
	time_captured = time_c;
	
	// No Compression for frame_captures
	frame_options.compression = frame_options.NONE;
};

void Recorder::newRecording(unsigned int framerate, QDir p_dir, QString r_name, bool cap_frames) {
	stopRecording();

	// check if directory is a directory and  is writable
	project_dir = p_dir;

	QFileInfo pDirInfo(project_dir.path());
	if(!pDirInfo.isDir() || !pDirInfo.isWritable()) {
		throw RecorderError::INVALID_PROJECT_DIRECTORY;
		return;
	}

	rec_name = r_name;
	capture_frames = cap_frames;

	// Verify Recdir... create directories...
	QDir record_dir(project_dir.path() + rec_name);
	RecorderError err = verifyRecDir();
	if(err != RecorderError::OK) {
		throw err;
		return;
	}

	// get Status file
	QFile stat_file(project_dir.path() + rec_name + ".stat");
	if(!stat_file.open(QIODevice::ReadWrite | QIODevice::Text)) {
		throw RecorderError::CANT_OPEN_STATFILE;
		return;
	}

	// If append, figure out Frame count etc...
	if(append) {
		if(!restoreRecording()) {
			throw RecorderError::STATFILE_ERROR;
			return;
		}
	}

	Error f_err;

	// set recorder options
	options.frameRate = framerate;

	// open AVI in recorder
	f_err = recorder.AVIOpen((record_dir.path() + rec_name).toStdString().c_str(), &options);
	if (f_err != PGRERROR_OK)
	{
		throw f_err;
		return;
	}

	is_recording = true;
};

bool Recorder::restoreRecording() {
	bool ok;
	frame_n = stat_file.readLine().toInt(&ok, 10);

	return ok;
}

RecorderError Recorder::verifyRecDir() {
	// check if project with same name exists and append to that
	// TODO: chech if there is any option to append
	// TODO: Check for special chars.
	
	if(rec_name == "") {
		return	RecorderError::INVALID_RECORDING_NAME;
		cleanup();
	}
	
       	if(record_dir.exists()) {		
		QMessageBox msgBox;
	     
		msgBox.setText(tr("A recording with this name already exists. Which action should be taken?"));
		void *appendButton = msgBox.addButton(tr("Append the recording."), QMessageBox::ActionRole);
		void *removeButton = msgBox.addButton(tr("Overwrite recording."), QMessageBox::ActionRole);
		void *abortButton = msgBox.addButton(QMessageBox::Abort);

		msgBox.exec();

		if (msgBox.clickedButton() == appendButton) {
			append = true;
		} else if (msgBox.clickedButton() == removeButton) {
			record_dir.removeRecursively();
       		} else if (msgBox.clickedButton() == abortButton) {
			return RecorderError::CANCELED;
		}
	}

	project_dir.mkdir(rec_name);
       	if(capture_frames)
		record_dir.mkdir("frames");

	return RecorderError::OK;
}

void Recorder::stopRecording() {
	if(is_recording) {
		// Stop Recorder
		Error err = recorder.AVIClose();
		if(err != PGRERROR_OK) {
			throw err;
			return;
		}

		is_recording = false;
		cleanup();
	} 
}

void Recorder::cleanup() {
	// Reset Everything	
	if(!is_recording) {
		frame_n = 0;
		time_c =  0;
		project_dir = "";
		rec_name = "";
		capture_frames = false;
		append = false;
	}
};

void Recorder::appendFrame(FlyCapture2::Image *image) {
	// If not recording, just stop.
	if(!is_recording)
		return;
	
	Error app_err = recorder.AVIAppend(image);
	if(app_err != PGRERROR_OK) {
		throw app_err;
		return;
	}

	// save image as frame
	if(capture_frames) {
		app_err = image->Save((record_dir.path() + "frames/" + frame_n).toStdString().c_str(), &frame_options);
		if(app_err != PGRERROR_OK) {
			throw app_err;
			return;
		}
	}

	frame_n++;
	time_c = frame_n / options.frameRate;
}
