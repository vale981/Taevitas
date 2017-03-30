#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QImage>
#include <QGraphicsItem>
#include <QDebug>
#include <QTime>
#include <QErrorMessage>
#include <QFileDialog>
#include <QCloseEvent>
#include <QTimer>

// TODO: Handle Errors!!
// TODO: Handle Disconnect!!
// TODO: Started Capture Event...

MainWindow::MainWindow( QWidget * parent ) :
    QMainWindow( parent ),
    ui( new Ui::MainWindow ),
    camMan( this ),
    recorder( 0, 18, false ),
    resize { false },
    comm( this ) {
    ui->setupUi( this );

    // Set Scene and Hide Preview Widget
    ui->preview_widget->hide();

    // Hide Serial Control
    ui->serialControl->setProperty( "visible", false );

    fit();

    // Set status
    setStatus( WAITING );

    // Try to connect to first cam
    scanAndUpdateCameras();

    // Fill serial ports.
    fillSerialPorts();

    // Set default name
    ui->projectName->setText( "Taevitas_Rec_" + QDateTime::currentDateTime().toString( "dd_MM_yyyy_hh_mm_ss" ) );

    // Set default dir
    QString defaultDir = QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation );
    recorder.setProjectDir( defaultDir );

    // TODO: Finish -> quit
    // Move Recorder into another thread
    recThread = new QThread();
    recorder.moveToThread( recThread );
    recThread->start();
    connect( recThread, &QThread::finished, recThread, &QThread::deleteLater );

    // Initialize Image buffer.
    image_buffer = new QVector<FlyCapture2::Image *>;

    // Connect Frame Counts, Time Captured LCD
    connect( &recorder, &Recorder::frameSaved, this, &MainWindow::frameSaved );

    // Connect ImageWriteSignal
    connect( this, &MainWindow::saveFrame, &recorder, &Recorder::appendFrame, Qt::QueuedConnection );

    // Connect Events
    connect( ui->preview_button, &QPushButton::clicked, this, &MainWindow::togglePreview );

    // Rescan Cameras
    connect( ui->camScanButton, &QPushButton::clicked, this, &MainWindow::scanAndUpdateCameras );

    // Rescan Serials
    connect( ui->serialScanButton, &QPushButton::clicked, this, &MainWindow::fillSerialPorts );

    // Serial Control Buttons
    connect( ui->sRun, &QPushButton::clicked, &comm, &SerialCommunicator::sendRun );
    connect( ui->sHalt, &QPushButton::clicked, &comm, &SerialCommunicator::sendHalt );
    connect( ui->sFast, &QPushButton::clicked, &comm, &SerialCommunicator::sendFast );

    // Camera selected
    connect( ui->cameraSelector, static_cast<void( QComboBox::* )( int )>( &QComboBox::currentIndexChanged ), this, &MainWindow::cameraSelected );

    // Serial Selected
    connect( ui->serialSelector, static_cast<void( QComboBox::* )( int )>( &QComboBox::currentIndexChanged ), this, [this] ( int port ) {
        ui->serialControl->setProperty( "visible", comm.selectPort( port ) );
    } );

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

    // Serial Selected
    connect( &comm, &SerialCommunicator::dataRead, this, [this] ( QByteArray data ) {
        qDebug() << data;
    } );
}

// TODO: Proper wait please! EVENT
MainWindow::~MainWindow() {
    delete ui;
    delete image_buffer;
    recThread->quit();
    recThread->wait();
    delete recThread;
}

void MainWindow::closeEvent ( QCloseEvent * event ) {
    // TODO: Nicer
    if ( status == RECORDING ) {
        startStopRecording();
        event->ignore();
        QTimer::singleShot( 1000, this, &MainWindow::close );
        return;
    } else if ( status == STOPPING ) {
        event->ignore();
        QTimer::singleShot( 1000, this, &MainWindow::close );
        return;
    }
    event->accept();
}

void MainWindow::setStatus( STATUS status ) {
    this->status = status;

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
        case STOPPING:
            ui->startButton->setText( "Stopping..." );
            ui->statusLabel->setText( "Stopping..." );

            disableRecOptions();
            break;
    }
}

// FIXME
void MainWindow::fit() {
    setMinimumSize( 0, 0 );
    setMaximumSize( 5000, 5000 );
    adjustSize();
    //setFixedSize( this->size() );
}

void MainWindow::updateCameraList( unsigned int num_cameras ) {
    ui->cameraSelector->clear();

    // Fill Combo Box with cameras
    for ( unsigned int i = 0; i < num_cameras; i++ ) {
        ui->cameraSelector->addItem( QString( i + '0' ) );
    }
}

void MainWindow::fillSerialPorts() {
    ui->serialSelector->clear();

    auto ports = comm.getPorts();

    // Fill Combo Box with Serial Ports
    if ( ports.length() > 0 ) {
        for ( QSerialPortInfo &info : ports ) {
            ui->serialSelector->addItem( info.portName() );
        }

        // TODO: Method for that
        ui->serialControl->setProperty( "visible", comm.selectPort( 0 ) );
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
    static QMutex m;
    m.lock();

    // If preview is activated...
    if ( ui->preview_widget->isEnabled() )
        displayPreview( image );

    if ( recorder.isRecording() ) {
        // TODO: WHY POINTER
        image_buffer->append( image );
        ui->buffer->display( image_buffer->length() );
        emit saveFrame( image );
    } else
        delete image;

    m.unlock();
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
        if ( !recorder.isRecording() )
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


        try {
            recorder.newRecording( ui->projectName->text() );
        } catch ( RecorderError ) {
            showError( "Could not start Recording!" );
            ui->saveFrames->setProperty( "enabled", true );
            resetCapture();
            return;
        }

        if ( !camMan.isCapturing() ) {
            try {
                camMan.startCapture();
            } catch ( FlyCapture2::Error e ) {
                showError( e );
                ui->saveFrames->setProperty( "enabled", true );
                return;
            }
        }

        // FIXME: Why doesn't that work?
        setStatus( RECORDING );
        setLcd();

    } else {
        // Stop Capture!
        try {
            camMan.stopCapture();
        } catch ( FlyCapture2::Error e ) {
            showError( e );
            return;
        }

        if ( image_buffer->length() > 0 ) {
            // We just wait...
            setStatus( STOPPING );
            return;
        }

        try {
            recorder.stopRecording();
        } catch ( FlyCapture2::Error e ) {
            showError( e );
            return;
        }

        resetCapture();

        ui->saveFrames->setProperty( "enabled", true );
        setStatus( CONNECTED );
    }
}

void MainWindow::resetCapture() {
    if ( !ui->preview_button->isChecked() ) {
        try {
            camMan.stopCapture();
        } catch ( FlyCapture2::Error e ) {
            showError( e );
            return;
        }
    } else {
        try {
            camMan.startCapture();
        } catch ( FlyCapture2::Error e ) {
            showError( e );
        }
    }
}

void MainWindow::frameSaved( FlyCapture2::Image * image ) {
    static QMutex m;
    m.lock();

    setLcd();

    // Search and Delete (Should be first).

    for ( int i = 0; i < image_buffer->length(); i++ ) {
        if ( ( *image_buffer )[i] == image ) {
            delete ( *image_buffer )[i];
            image_buffer->remove( i );
            break;
        }
    }

    ui->buffer->display( image_buffer->length() );
    if ( status == STOPPING && image_buffer->empty() )
        startStopRecording();

    comm.sendBuffer( image_buffer->length() );
    m.unlock();
}

void MainWindow::setLcd() {
    qDebug() << "setting lcd";
    ui->framesCaptured->display( recorder.frameNumber() );
    ui->timeCaptured->display( QString( "%1:%2" ).arg( ( ( ( int )recorder.timeCaptured() ) / 60 ) ).arg( ( int )recorder.timeCaptured() % 60 ) );
}
