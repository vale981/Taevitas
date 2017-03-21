#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QImage>
#include <QGraphicsItem>
#include <QDebug>
#include <QTime>
#include <QErrorMessage>

// TODO: Handle Errors!!

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    cam_man(this),
    recorder(this)
{
    ui->setupUi(this);

    // Set Scene and Hide Preview Widget
    ui->preview_widget->hide();
    adjustSize();
    
    disableRecOptions();
    
    // Try to connect to first cam
    scanAndUpdateCameras();
    
    // Set default name
    ui->projectName->setText("Taevitas_Rec_" + QDateTime::currentDateTime().toString("dd_MM_yyyy_hh_mm_ss"));

    // Connect Events
    connect(ui->preview_button, &QPushButton::clicked, this, &MainWindow::toggle_preview);

    // Cam ComboBox clicked
    connect(ui->camScanButton, &QPushButton::clicked, this, &MainWindow::scanAndUpdateCameras);
    
    // Camera selected
    connect(ui->cameraSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &MainWindow::camera_selected);
    
    // Frame Captured
    connect(&cam_man, &CameraManager::frameCaptured, this, &MainWindow::frame_captured, Qt::DirectConnection);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::updateCameraList(unsigned int num_cameras) {
    ui->cameraSelector->clear();

    // Fill Combo Box with cameras
    for (unsigned int i = 0; i < num_cameras; i++) {
        ui->cameraSelector->addItem(QString(i+'0'));
    }
}

void MainWindow::scanAndUpdateCameras() {
    unsigned int num_cameras = cam_man.numCameras();
    updateCameraList(num_cameras);
    if(num_cameras > 0 && !cam_man.isConnected())
        camera_selected(0);
};

void MainWindow::disableRecOptions() {
    ui->recOptions->setProperty("enabled", false);
}

void MainWindow::enableRecOptions() {
    ui->recOptions->setProperty("enabled", true);
}

void MainWindow::showError(QString error) {
    QMessageBox errBox;
    errBox.critical(0,"Error", "An Error has occured:\n" + error);
    errBox.setFixedSize(500,200);
    errBox.show();
}

void MainWindow::showError(FlyCapture2::Error error) {
    showError(error.GetDescription());
}

void MainWindow::camera_selected(int index) {
    if(recorder.isRecording() || index < 0)
        return;
    
    try {
        cam_man.connectCamera(index);
    } catch (FlyCapture2::Error e) {
        showError(e);
        return;
    }
    
    enableRecOptions();
};

// Show/Hide Preview
void MainWindow::toggle_preview(bool checked) {
    // skip if there is no camera
    if(!cam_man.isConnected()) {
        ui->preview_button->setProperty("checked", false);
        return;
    }
        
    if(checked) {
        ui->preview_widget->setProperty("enabled", true);
        ui->preview_widget->show();

        // Start Capturing for preview
        try {
            cam_man.startCapture();
        } catch (FlyCapture2::Error e) {
            showError(e);
        }
    } else {
        ui->preview_widget->setProperty("enabled", false);
        ui->preview_widget->hide();

        //Stop capture
        if(!recorder.isRecording())
            cam_man.stopCapture();
    }
    
    adjustSize();
}

void MainWindow::frame_captured(FlyCapture2::Image* image) {
    qDebug() << "Image Captured!";
    // If preview is activated...
    if(ui->preview_widget->isVisible())
        displayPreview(image);
    return;
}

void MainWindow::displayPreview(FlyCapture2::Image* last_capture) {
    // Convert Pixel Format to RGB
    FlyCapture2::Image last_image;
    FlyCapture2::Error e = last_capture->Convert(FlyCapture2::PIXEL_FORMAT_RGB16, &last_image);
    qDebug() << *last_capture->GetData();
    last_preview_image = QImage(last_image.GetData(), last_capture->GetCols(), last_capture->GetRows(), QImage::Format::Format_RGB16);

    ui->preview_widget->setFixedSize(last_capture->GetCols(), last_capture->GetRows());

    last_preview.convertFromImage(last_preview_image);

    ui->preview_widget->setPixmap(last_preview);
}
