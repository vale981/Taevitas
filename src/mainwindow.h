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
        Ui::MainWindow * ui;
        CameraManager camMan;
        Recorder recorder;

        void displayPreview( FlyCapture2::Image * last_capture );
        void disableRecOptions();
        void enableRecOptions();
        void enableStart();

        void showError( FlyCapture2::Error err );
        void showError( QString error );

        void updateCameraList( unsigned int num_cameras );

        enum STATUS {
            WAITING,
            CONNECTED,
            RECORDING,
            STOPPING
        } status;

        void setStatus( STATUS status );

        bool resize;

        QVector<FlyCapture2::Image *> * image_buffer;

        QThread * recThread;

        void setLcd();


        // Starts or Stops the capture, depeending on if it is already running.
        // Throws FlyCapture2::Error;
        void resetCapture();

        SerialCommunicator comm;

    private slots:
        // Fills Camera Combobox with Cameras
        void scanAndUpdateCameras();

        void togglePreview( bool );
        void frameCaptured( FlyCapture2::Image * image );
        void cameraSelected( int index );
        void directorySelection();
        void startStopRecording();
        void frameSaved( FlyCapture2::Image * image );

        void fillSerialPorts();

        void handleCaptureError( FlyCapture2::Error err );
        void handleWriteError( FlyCapture2::Error err );
        void fit();

    signals:
        void saveFrame( FlyCapture2::Image * image );
};

#endif // MAINWINDOW_H
