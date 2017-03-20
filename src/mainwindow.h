#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cameramanager.h"
#include "recorder.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include "FlyCapture2.h"
#include <QPixmap>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	
private:
	Ui::MainWindow *ui;
	CameraManager cam_man;
	Recorder recorder;
    FlyCapture2::Image last_capture;
    QPixmap last_preview;

	void displayPreview(FlyCapture2::Image* image);
	void disableRecOptions();
	void enableRecOptions();

	void showError(FlyCapture2::Error err);
	void showError(QString error);

	void updateCameraList(unsigned int num_cameras);
			      
private slots:
	// Fills Camera Combobox with Cameras
	void scanAndUpdateCameras();

	void toggle_preview(bool);
	void frame_captured(FlyCapture2::Image* image);
	void camera_selected(int index);
};

#endif // MAINWINDOW_H
