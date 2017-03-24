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
        void stopCapture( bool force = false );

    private slots:
        // Fills Camera Combobox with Cameras
        void scanAndUpdateCameras();

        void togglePreview( bool );
        void frameCaptured( FlyCapture2::Image * image );
        void cameraSelected( int index );
        void directorySelection();
        void startStopRecording();
};

#endif // MAINWINDOW_H
