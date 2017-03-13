#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cameramanager.h"
#include "recorder.h"
#include <QMainWindow>

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

private slots:
	void toggle_preview(bool);

};

#endif // MAINWINDOW_H
