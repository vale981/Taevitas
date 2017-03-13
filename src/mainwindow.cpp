#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    cam_man(qobject_cast<QObject*>(this)),
    recorder(qobject_cast<QObject*>(this))
{
    ui->setupUi(this);

    // Hide Preview Widget
    ui->preview_widget->hide();
    adjustSize();

    // Connect Events
    connect(ui->preview_button, &QPushButton::clicked, this, &MainWindow::toggle_preview);
}

MainWindow::~MainWindow() {
    delete ui;
}

// Show/Hide Preview
void MainWindow::toggle_preview(bool checked) {
    if(checked) {
        ui->preview_widget->setProperty("enabled", true);
        ui->preview_widget->show();
    } else {
        ui->preview_widget->setProperty("enabled", false);
        ui->preview_widget->hide();
    }
    
    adjustSize();

    // Start Capturing for preview
}


