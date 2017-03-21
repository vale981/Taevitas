#ifndef RECORDER_H
#define RECORDER_H

#include <String>
#include <QObject>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QMessageBox>
#include <QAbstractButton>
#include "FlyCapture2.h"

/*
  This class is a wrapper around the AVIRecorder from PTGrey to abstract and implement signals.
 */

enum class RecorderError {
	INVALID_PROJECT_DIRECTORY,
	INVALID_RECORDING_NAME,
	CREATION_RECORD_DIRECTORY_FAILED,
	CANCELED,
	CANT_OPEN_STATFILE,
	STATFILE_ERROR,
	OK
};

class Recorder : QObject {
	Q_OBJECT

public:
	// Set bitrate to a default of 10Mbit.
	Recorder(QObject *parent = 0);
	~Recorder();

	// Start a recording. A recording directory with the avi files and evtl. a frame subfolder will be created. Throws RecorderError or FlyCapture2::Error
	void newRecording(unsigned int framerate, QDir p_dir, QString r_name, bool capture_frames = false);

	// Append a frame to the recording,
	void appendFrame(FlyCapture2::Image *image);
	
	// stops the recording, cleans up, throws FlyCapture2::Error
	void stopRecording();

	QString getRecordingFileName() {		
		return rec_name;
	}

	QString getRecName() {
		return rec_name;
	}

	bool isRecording() {
		return is_recording;
	}
	
	const unsigned int& frame_number;
	const double& time_captured;

private:
 	FlyCapture2::AVIRecorder recorder;
	FlyCapture2::AVIOption options;
	FlyCapture2::TIFFOption frame_options;

	// Basic state Variable, because AVIRecorder doesn't provide it.
	bool is_recording;

	// append to existing files
	bool append;

	// save individual frames as image files
	bool capture_frames;

	// number of frames captured
	unsigned int frame_n;
	double time_c;
	
	QDir project_dir;
	QDir record_dir;
	QString rec_name;

	// status file for frame count
	QFile stat_file;

	// Check if recording directory exists. If it does ask for Overwrite or cancelation.
	RecorderError verifyRecDir();

	// If appending, check if there are any information about existing frames...
	bool restoreRecording();

	// reset Status, only if not recording (is_recording == false).
	void cleanup();
};
#endif //RECORDER_H
