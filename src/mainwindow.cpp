#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QImage>
#include <QGraphicsItem>
#include <QDebug>

// TODO: Handle Errors!!

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    cam_man(this),
    recorder(this)
{
    ui->setupUi(this);

    // Set Scene and Hide Preview Widget
    ui->preview_widget->setScene(&current_preview_scene);
    ui->preview_widget->hide();
    adjustSize();

    // Fill Combo Box with cameras
    unsigned int num_cameras = 10; //cam_man.numCameras();
    for (unsigned int i = 0; i < num_cameras; i++) {
        ui->cameraSelector->addItem(QString(i+'0'));
    }
        
    // Connect Events
    connect(ui->preview_button, &QPushButton::clicked, this, &MainWindow::toggle_preview);
    connect(ui->cameraSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated), this, &MainWindow::camera_selected);
    connect(&cam_man, &CameraManager::frameCaptured, this, &MainWindow::frame_captured);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::camera_selected(int index) {
    qDebug() << index;
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
    } else {
        ui->preview_widget->setProperty("enabled", false);
        ui->preview_widget->hide();
    }
    
    adjustSize();

    // Start Capturing for preview
    cam_man.startCapture();
}

void MainWindow::frame_captured(FlyCapture2::Image* image) {
    // If preview is activated...
    if(ui->preview_widget->isVisible())
        displayPreview(image);
}

void MainWindow::displayPreview(FlyCapture2::Image* image) {
    // Convert Pixel Format to RGB
    FlyCapture2::Image conv_img;
    image->Convert(FlyCapture2::PixelFormat::PIXEL_FORMAT_RGB16, &conv_img);

    current_preview_scene.clear();
    QImage tmp(image->GetData(), image->GetCols(), image->GetRows(), QImage::Format::Format_RGB16);
    current_preview_scene.addItem(new QGraphicsPixmapItem(QPixmap::fromImage(tmp)));
}
