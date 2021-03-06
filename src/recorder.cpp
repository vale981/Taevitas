#include "recorder.h"
#include <QDebug>
#include <QRegExp>

using namespace FlyCapture2;

const QHash<RecorderError::_RecorderError, QString> RecorderError::_description = {
    { RecorderError::INVALID_PROJECT_DIRECTORY, "Invalid Project Directory!" },
    { RecorderError::INVALID_RECORDING_NAME, "Invalid Recording Name!" },
    { RecorderError::CREATION_RECORD_DIRECTORY_FAILED, "The creation of the recording directory failed." },
    { RecorderError::CANCELED, "Operation Canceled" },
    { RecorderError::CANT_OPEN_STATFILE, "Failed to open the statfile." },
    { RecorderError::STATFILE_ERROR, "Error with (corrupted/malformed) statfile.\nPlease consider to create a new project, to prevent damage to the corrupted one." },
    { RecorderError::OK, "All went OK." },
};

Recorder::Recorder( QObject * parent, unsigned int frame_rate, bool cap_frames ) :
    QObject( parent ),
    is_recording {false},
    pDirSet { false },
    append {false},
    frame_n {0},
    time_c {0} {
    // No Compression for frame_captures
    frame_options.compression = frame_options.NONE;
    options.frameRate = frame_rate;
    capture_frames = cap_frames;
}

Recorder::~Recorder() {
    stopRecording();
}

void Recorder::newRecording( QString r_name ) {
    stopRecording();

    // If unset.
    if ( !dirSet() ) {
        throw RecorderError( RecorderError::INVALID_PROJECT_DIRECTORY );
        return;
    }

    if ( r_name.length() == 0 ) {
        throw RecorderError( RecorderError::INVALID_RECORDING_NAME );
        return;
    }

    // Clean r_name //TODO: TEST // NOTE: Maybe Visual Feedback for that...
    r_name.replace( QRegExp( "[^\\_a-zA-Z0-9]" ), "_" );
    recName = r_name;

    // Verify Recdir... create directories...
    record_dir = QDir( baseDir.path() + "/" + recName );
    // Change to try/catch
    RecorderError err = verifyRecDir();
    if ( err != RecorderError::OK ) {
        throw err;
        return;
    }

    bool statExists = QFile( record_dir.path() + "/" + ".stat" ).exists();

    // get Status file
    statFile = new QFile(  record_dir.path() + "/" + ".stat" );
    if ( !statFile->open( QIODevice::ReadWrite | QIODevice::Text ) ) {
        throw RecorderError( RecorderError::CANT_OPEN_STATFILE );
        return;
    }

    if ( !statExists ) {
        statFile->write( "0" );
    }

    frame_n = 0;
    time_c = 0;

    // If append, figure out Frame count etc...
    if ( append ) {
        if ( !restoreRecording() ) {
            throw RecorderError( RecorderError::STATFILE_ERROR );
            return;
        }
        time_c = frame_n / options.frameRate;
    }

    // open AVI in recorder
    Error f_err;
    f_err = recorder.AVIOpen( ( record_dir.path() + "/" + recName + "_" + QString::number( frame_n ) + ".avi" ).toStdString().c_str(), &options );
    if ( f_err != PGRERROR_OK ) {
        throw f_err;
        return;
    }

    is_recording = true;
}

void Recorder::stopRecording() {
    if ( is_recording ) {
        // Stop Recorder
        Error err = recorder.AVIClose();
        if ( err != PGRERROR_OK ) {
            throw err;
            return;
        }

        is_recording = false;
        cleanup();
    }
}

void Recorder::setProjectDir( QString &p_dir ) {
    QFileInfo pDirInfo( p_dir );
    if ( !pDirInfo.isDir() || !pDirInfo.isWritable() ) {
        throw RecorderError( RecorderError::INVALID_PROJECT_DIRECTORY );
        return;
    }

    baseDir = QDir( p_dir );
    pDirSet = true;
}

bool Recorder::restoreRecording() {
    bool ok;

    QByteArray tmp = statFile->readLine();
    frame_n = QString( tmp ).toUInt( &ok );

    return ok;
}

RecorderError Recorder::verifyRecDir() {
    // check if project with same name exists and append to that

    if ( record_dir.exists() ) {
        QMessageBox msgBox;

        msgBox.setText( tr( "A recording with this name already exists. Which action should be taken?" ) );
        void * appendButton = msgBox.addButton( tr( "Append the recording" ), QMessageBox::ApplyRole );
        void * removeButton = msgBox.addButton( tr( "Overwrite recording" ), QMessageBox::ActionRole );
        void * abortButton = msgBox.addButton( QMessageBox::Abort );

        msgBox.exec();

        if ( msgBox.clickedButton() == appendButton ) {
            append = true;
        } else if ( msgBox.clickedButton() == removeButton ) {
            record_dir.removeRecursively();
        } else if ( msgBox.clickedButton() == abortButton ) {
            return RecorderError( RecorderError::CANCELED );
        }
    }

    baseDir.mkdir( recName );

    if ( capture_frames )
        record_dir.mkdir( "frames" );

    return RecorderError( RecorderError::OK );
}

void Recorder::appendFrame( FlyCapture2::Image * image ) {
    write_lock.lock();
    qDebug() << "Writing Frame...";

    // If not recording, just stop.
    if ( !is_recording )
        return;

    Error app_err = recorder.AVIAppend( image );
    if ( app_err != PGRERROR_OK ) {
        write_lock.unlock();
        emit writeError( app_err.GetDescription() );
        return;
    }

    // save image as frame
    if ( capture_frames ) {
        app_err = image->Save( ( record_dir.path() + "/frames/" + recName + "_" + QString::number( frame_n ) + ".tiff"  ).toStdString().c_str(), &frame_options );
        if ( app_err != PGRERROR_OK ) {
            write_lock.unlock();
            emit writeError( app_err.GetDescription() );
            return;
        }
    }

    frame_n++;
    time_c = frame_n / options.frameRate;


    // Go to begining.
    statFile->seek( 0 );
    // Write Frames to Stat File.
    statFile->write( QByteArray::number( frame_n ) );

    emit frameSaved( image );
    write_lock.unlock();
}

void Recorder::cleanup() {
    // Reset Everything
    if ( !is_recording ) {
        frame_n = 0;
        time_c =  0;
        append = false;
        delete statFile;
    }
}
