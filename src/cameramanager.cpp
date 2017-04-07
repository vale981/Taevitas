#include "cameramanager.h"
#include <QDebug>
#include <QMutex>

using namespace FlyCapture2;

CameraManager::CameraManager( QObject * parent ) :
    QObject( parent ),
    num_cameras {0},
    is_capturing {false},
    camera_index {-1} {
    bus_mgr.RegisterCallback( &CameraManager::camConnectEvent, ARRIVAL, this, &handleC );
    bus_mgr.RegisterCallback( &CameraManager::camDisconnectEvent, REMOVAL, this, &handleD );
}

CameraManager::~CameraManager() {
    bus_mgr.UnregisterCallback( handleC );
    bus_mgr.UnregisterCallback( handleD );

    stopCapture();
    camera.Disconnect();
}

void CameraManager::connectCamera( int index ) {
    // Don't connect twice.
    if ( camera_index == index )
        return;

    Error error; // general purpose error object
    if ( camera.IsConnected() ) {
        error = camera.Disconnect();
        if ( error != PGRERROR_OK ) {
            throw error;
            return;
        }
    }

    qDebug() << "Connecting to camera: " << index << '\n';

    // get PGRGuid of the Camera
    BusManager bus_mgr;
    error = bus_mgr.GetCameraFromIndex( index, &camera_guid );
    if ( error != PGRERROR_OK ) {
        throw error;
        return;
    }

    // connectCamera
    error = camera.Connect( &camera_guid );
    if ( error != PGRERROR_OK ) {
        throw error;
        return;
    }

    cam_config = FlyCapture2::FC2Config();
    cam_config.grabMode = GrabMode::BUFFER_FRAMES;
    cam_config.numBuffers = 10; // We gonna move them into our own data structure.
    cam_config.highPerformanceRetrieveBuffer = false; // We want to trigger.
    camera.SetConfiguration( &cam_config );

    camera_index = index;
}

void CameraManager::startCapture() {
    // Don't capture twice!
    if ( is_capturing )
        return;

    Error error;
    error = camera.StartCapture();

    if ( error != PGRERROR_OK ) {
        throw error;
        return;
    }

    // Just my own async image grabbing!
    ImageGrabber * tmpG = new ImageGrabber( this );
    tmpG->setCamera( &camera );
    connect( tmpG, &ImageGrabber::imageCaptured, this, &CameraManager::frameCaptured, Qt::QueuedConnection );
    connect( tmpG, &ImageGrabber::finished, tmpG, &ImageGrabber::deleteLater );
    connect( tmpG, &ImageGrabber::captureError, this, &CameraManager::captureError );
    tmpG->start();

    grabber = tmpG;
    is_capturing = true;
}

void CameraManager::stopCapture() {
    if ( !is_capturing )
        return;

    grabber->stopCapturing();

    Error error = camera.StopCapture();
    if ( error != PGRERROR_OK ) {
        throw error;
        return;
    }

    grabber->wait();

    is_capturing = false;
}

void CameraManager::camConnectEvent( void * pParameter, unsigned int serialNumber ) {
    static_cast<CameraManager *>( pParameter )->cameraConnected();
}

void CameraManager::camDisconnectEvent( void * pParameter, unsigned int serialNumber ) {
    CameraManager * cam = static_cast<CameraManager *>( pParameter );
    FlyCapture2::CameraInfo info;

    cam->camera.GetCameraInfo( &info );
    bool current = ( serialNumber == info.serialNumber );

    cam->cameraDisconnected( current );
}
