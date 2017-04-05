#ifndef RECORDER_H
#define RECORDER_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QStandardPaths>
#include <QMessageBox>
#include <QAbstractButton>
#include <QMutex>
#include <QHash>
#include "FlyCapture2.h"

/*
  This class is a wrapper around the AVIRecorder from PTGrey to abstract and implement signals.
 */

class RecorderError {
        Q_OBJECT

    public:
        enum _RecorderError {
            INVALID_PROJECT_DIRECTORY,
            INVALID_RECORDING_NAME,
            CREATION_RECORD_DIRECTORY_FAILED,
            CANCELED,
            CANT_OPEN_STATFILE,
            STATFILE_ERROR,
            OK
        };

        RecorderError( _RecorderError _err ) : Error { _err } {}

        const QString what() {
            // Will propably only be looked up once :)
            return _description[Error];
        }

        _RecorderError error() {
            return Error;
        }

        bool operator==( const RecorderError &other ) const {
            return Error == other.Error;
        }

        bool operator!=( const RecorderError &other ) const {
            return !( Error == other.Error );
        }

        static const QHash<_RecorderError, QString> _description;

    private:
        _RecorderError Error;
};


class Recorder : public QObject {
        Q_OBJECT

    public:
        // Set bitrate to a default of 10Mbit.
        Recorder( QObject * parent = 0, unsigned int frame_rate = 18, bool cap_frames = false );
        ~Recorder();

        // Start a recording. A recording directory with the avi files and evtl. a frame subfolder will be created. Throws RecorderError or FlyCapture2::Error
        void newRecording( QString r_name );

        // stops the recording, cleans up, throws FlyCapture2::Error
        void stopRecording();

        void setProjectDir( QString &p_dir );
        QString getProjectDir() {
            return baseDir.absolutePath();
        }

        bool isRecording() {
            return is_recording;
        }

        int frameNumber() const {
            return frame_n;
        }

        double timeCaptured() const {
            return time_c;
        }

        QString getRecName() {
            return recName;
        }

        unsigned int getFrameRate() {
            return options.frameRate;
        }

        void setFrameRate( unsigned int frame_rate ) {
            options.frameRate = frame_rate;
        }

        bool dirSet() {
            return pDirSet && !baseDir.absolutePath().isEmpty();
        }

        bool captureFrames() {
            return capture_frames;
        }

    public slots:
        // Append a frame to the recording,
        void appendFrame( FlyCapture2::Image * image );

        void setCaptureFrames( bool set ) {
            capture_frames = set;
        }

    private:
        FlyCapture2::AVIRecorder recorder;
        FlyCapture2::AVIOption options;
        FlyCapture2::TIFFOption frame_options;

        // lock the appendFrame function.
        QMutex write_lock;

        // basic state Variable, because AVIRecorder doesn't provide it.
        // Well it does, but it is boring to look it up.
        bool is_recording;

        // Indicates wether the project directorie is set.
        bool pDirSet;

        // append to existing files
        bool append;

        // save individual frames as image files
        bool capture_frames;

        // number of frames captured
        int frame_n;
        double time_c;

        // recording config
        QDir baseDir;
        QDir record_dir;
        QString recName;

        // status file for frame count
        QFile * statFile;

        // Check if recording directory exists. If it does ask for Overwrite or cancelation.
        RecorderError verifyRecDir();

        // If appending, check if there are any information about existing frames...
        bool restoreRecording();

        // reset Status, only if not recording (is_recording == false).
        void cleanup();

    signals:
        void frameSaved( FlyCapture2::Image * image );
        void writeError( FlyCapture2::Error err );
};
#endif //RECORDER_H
