#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include "FlyCapture2.h"
#include "cameramanager.h"
#include "recorder.h"
#include "serialcommunicator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow( QWidget * parent = 0 );
        ~MainWindow();

    protected:
        void closeEvent( QCloseEvent * event );

    private:
        enum STATUS {
            WAITING,
            CONNECTED,
            RECORDING,
            STOPPING
        } status;
        void setStatus( STATUS status );

        Ui::MainWindow * ui;
        CameraManager camMan;
        Recorder recorder;
        SerialCommunicator comm;
        QThread * recThread;
        bool resize;
        QVector<FlyCapture2::Image *> * image_buffer;

        void showError( FlyCapture2::Error err );
        void showError( QString error );
        void setLcd();

        void updateCameraList( unsigned int num_cameras );

        void enableStart();
        void enableRecOptions();
        void disableRecOptions();

        // Starts or Stops the capture, depeending on if it is already running.
        // Throws FlyCapture2::Error;
        void resetCapture();

        // Show an Image in the Preview Widget.
        void displayPreview( FlyCapture2::Image * last_capture );

        // Deletes Image on next Event Loop Cycle
        void deleteImage( FlyCapture2::Image * image );

    private slots:
        void startStopRecording();

        // Fills Camera Combobox with Cameras
        void scanAndUpdateCameras();
        void fillSerialPorts();

        // Show/Hide Preview
        void togglePreview( bool );

        void directorySelection();
        void selectSerialPort( int port );

        void cameraSelected( int index );
        void frameCaptured( FlyCapture2::Image * image );
        void frameSaved( FlyCapture2::Image * image );
        void handleCaptureError( QString err );
        void handleWriteError( QString err );

        void fit();

    signals:
        void saveFrame( FlyCapture2::Image * image );
};

#endif // MAINWINDOW_H
