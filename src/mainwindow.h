#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cameramanager.h"
#include "recorder.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include "FlyCapture2.h"

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
	QGraphicsScene current_preview_scene;

	void displayPreview(FlyCapture2::Image* image);

private slots:
	void toggle_preview(bool);
	void frame_captured(FlyCapture2::Image* image);
	void camera_selected(int index);
};

#endif // MAINWINDOW_H
