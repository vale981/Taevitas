#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QImage>
#include <QGraphicsItem>
#include <QDebug>
#include <QTime>
#include <QErrorMessage>
#include <QFileDialog>

// TODO: Handle Errors!!
// TODO: Status Label!!
// TODO: Handle Disconnect!!

MainWindow::MainWindow( QWidget * parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow ),
    camMan( this ),
    recorder( this, 18, false ),
    resize { false } {
    ui->setupUi( this );

    // Set Scene and Hide Preview Widget
    ui->preview_widget->hide();

    fit();

    // Set status
    setStatus( WAITING );

    // Try to connect to first cam
    scanAndUpdateCameras();

    // Set default name
    ui->projectName->setText( "Taevitas_Rec_" + QDateTime::currentDateTime().toString( "dd_MM_yyyy_hh_mm_ss" ) );

    // Connect Frame Counts, Time Captured LCD
    connect( &recorder, &Recorder::frameSaved, this, [this] {
        ui->framesCaptured->display( recorder.frameNumber() );
        ui->timeCaptured->display( QString( "%1:%2" ).arg( ( ( ( int )recorder.timeCaptured() ) / 60 ) ).arg( ( int )recorder.timeCaptured() % 60 ) );
    } );

    // Connect Events
    connect( ui->preview_button, &QPushButton::clicked, this, &MainWindow::togglePreview );

    // Cam ComboBox clicked
    connect( ui->camScanButton, &QPushButton::clicked, this, &MainWindow::scanAndUpdateCameras );

    // Camera selected
    connect( ui->cameraSelector, static_cast<void( QComboBox::* )( int )>( &QComboBox::currentIndexChanged ), this, &MainWindow::cameraSelected );

    // File Selector
    connect( ui->directorySelector, &QPushButton::clicked, this, &MainWindow::directorySelection );

    // Frame Captured
    connect( &camMan, &CameraManager::frameCaptured, this, &MainWindow::frameCaptured, Qt::DirectConnection );

    // Change Project Name
    connect( ui->projectName, &QLineEdit::textChanged, this, &MainWindow::enableStart );

    // Change Record Frames
    connect( ui->saveFrames, &QCheckBox::toggled, &recorder, &Recorder::setCaptureFrames );

    // Start recording
    connect( ui->startButton, &QPushButton::clicked, this, &MainWindow::startStopRecording );
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setStatus( STATUS status ) {
    switch ( status ) {
        case WAITING:
            disableRecOptions();
            ui->statusLabel->setText( "Waiting..." );
            ui->startButton->setText( "Start" );
            ui->recStats->hide();
            break;
        case CONNECTED:
            enableRecOptions();
            ui->statusLabel->setText( "Connected." );
            ui->startButton->setText( "Start" );
            ui->recStats->hide();
            qDebug( "Connected...." );
            break;
        case RECORDING:
            ui->timeCaptured->display( QString( "00:00" ) );
            ui->framesCaptured->display( 0 );

            ui->statusLabel->setText( "Recording!" );
            ui->startButton->setText( "Stop" );
            ui->recStats->show();
            break;

    }
}

void MainWindow::fit() {
    setMinimumSize( 0, 0 );
    setMaximumSize( 5000, 5000 );
    adjustSize();
    setFixedSize( this->size() );
}

void MainWindow::updateCameraList( unsigned int num_cameras ) {
    ui->cameraSelector->clear();

    // Fill Combo Box with cameras
    for ( unsigned int i = 0; i < num_cameras; i++ ) {
        ui->cameraSelector->addItem( QString( i + '0' ) );
    }
}

void MainWindow::scanAndUpdateCameras() {
    unsigned int num_cameras = camMan.numCameras();
    updateCameraList( num_cameras );
    if ( num_cameras > 0 && !camMan.isConnected() )
        cameraSelected( 0 );
}

void MainWindow::disableRecOptions() {
    ui->recOptions->setProperty( "enabled", false );
    ui->startButton->setProperty( "enabled", false );
}

void MainWindow::enableRecOptions() {
    ui->recOptions->setProperty( "enabled", true );
    enableStart();
}

void MainWindow::enableStart() {
    if ( ui->projectName->text() != "t" && recorder.dirSet() && camMan.isConnected() ) {
        ui->startButton->setProperty( "enabled", true );
    } else {
        ui->startButton->setProperty( "enabled", true );
    }
}

void MainWindow::showError( QString error ) {
    QMessageBox errBox;
    errBox.critical( 0, "Error", "An Error has occured:\n" + error );
    errBox.setFixedSize( 500, 200 );
    errBox.show();
}

void MainWindow::showError( FlyCapture2::Error error ) {
    showError( error.GetDescription() );
}

void MainWindow::cameraSelected( int index ) {
    if ( recorder.isRecording() || index < 0 )
        return;

    try {
        camMan.connectCamera( index );
    } catch ( FlyCapture2::Error e ) {
        showError( e );
        return;
    }

    setStatus( CONNECTED );
}

// Show/Hide Preview
void MainWindow::togglePreview( bool checked ) {
    // skip if there is no camera
    if ( !camMan.isConnected() ) {
        ui->preview_button->setProperty( "checked", false );
        return;
    }

    if ( checked ) {
        ui->preview_widget->setProperty( "enabled", true );
        resize = true;

        // Start Capturing for preview
        try {
            camMan.startCapture();
        } catch ( FlyCapture2::Error e ) {
            showError( e );
        }
    } else {
        ui->preview_widget->setProperty( "enabled", false );
        ui->preview_widget->hide();

        //Stop capture
        if ( !recorder.isRecording() )
            camMan.stopCapture();
    }
}

void MainWindow::frameCaptured( FlyCapture2::Image * image ) {
    qDebug() << "Image Captured!";

    // If preview is activated...
    if ( ui->preview_widget->isEnabled() )
        displayPreview( image );

    if ( recorder.isRecording() )
        recorder.appendFrame( image );

    return;
}

// Render Preview
void MainWindow::displayPreview( FlyCapture2::Image * last_capture ) {
    ui->preview_widget->show();

    FlyCapture2::Image last_image;
    QImage last_preview_image;
    QPixmap last_preview;

    // Convert Pixel Format to RGB
    FlyCapture2::Error e = last_capture->Convert( FlyCapture2::PIXEL_FORMAT_RGB, &last_image );

    last_preview_image = QImage( last_image.GetData(), last_image.GetCols(), last_image.GetRows(), QImage::Format_RGB888 );

    last_preview_image = last_preview_image.scaledToHeight( 500 );
    ui->preview_widget->setFixedSize( last_preview_image.width(), last_preview_image.height() );

    last_preview.convertFromImage( last_preview_image );
    ui->preview_widget->setPixmap( last_preview );

    if ( resize ) {
        fit();
        resize = false;
    }
}

void MainWindow::directorySelection() {
    QString dir = QFileDialog::getExistingDirectory( this, tr( "Choose the working Directory." ), ( recorder.dirSet() ? recorder.getProjectDir() : QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation ) ), QFileDialog::ShowDirsOnly );
    try {
        recorder.setProjectDir( dir );
        enableStart();
    } catch ( FlyCapture2::Error e ) {
        showError( e );
    }
}

void MainWindow::startStopRecording() {
    // TODO: Errors
    if ( !recorder.isRecording() ) {
        // TODO: Maybe allow dynamic setting...
        ui->saveFrames->setProperty( "enabled", false );

        if ( !camMan.isCapturing() ) {
            try {
                camMan.startCapture();
            } catch ( FlyCapture2::Error e ) {
                showError( e );
                ui->saveFrames->setProperty( "enabled", true );
                return;
            }
        }

        try {
            recorder.newRecording( ui->projectName->text() );
        } catch ( RecorderError ) {
            showError( "Could not start Recording!" );
            // TODO: Helper Method for cleanup
            ui->saveFrames->setProperty( "enabled", true );
            stopCapture();
            return;
        }

        setStatus( RECORDING );
    } else {
        // Stop Capture!
        try {
            camMan.stopCapture();
        } catch ( FlyCapture2::Error e ) {
            showError( e );
            return;
        }

        try {
            recorder.stopRecording();
        } catch ( FlyCapture2::Error e ) {
            showError( e );
            return;
        }

        // Restart Preview
        if ( ui->preview_button->isChecked() ) {
            try {
                camMan.startCapture();
            } catch ( FlyCapture2::Error e ) {
                showError( e );
            }
        }

        ui->saveFrames->setProperty( "enabled", true );
        setStatus( CONNECTED );
    }
}

void MainWindow::stopCapture() {
    if ( !ui->preview_button->isChecked() ) {
        try {
            camMan.stopCapture();
        } catch ( FlyCapture2::Error e ) {
            showError( e );
            return;
        }
    }
}
