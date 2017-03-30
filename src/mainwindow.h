#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include "FlyCapture2.h"
#include "cameramanager.h"
#include "recorder.h"

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
        void resetCapture();

        void fit();

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

    private slots:
        // Fills Camera Combobox with Cameras
        void scanAndUpdateCameras();

        void togglePreview( bool );
        void frameCaptured( FlyCapture2::Image * image );
        void cameraSelected( int index );
        void directorySelection();
        void startStopRecording();
        void frameSaved( FlyCapture2::Image * image );

    signals:
        void saveFrame( FlyCapture2::Image * image );
};

#endif // MAINWINDOW_H
