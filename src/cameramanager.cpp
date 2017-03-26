#include "cameramanager.h"
#include <QDebug>
#include <QMutex>

using namespace FlyCapture2;

CameraManager::CameraManager( QObject * parent ) : QObject( parent ), num_cameras {0}, camera_index {-1}, is_capturing {false} {
    image_buffer = new QVector<FlyCapture2::Image *>();
}

CameraManager::~CameraManager() {
    delete image_buffer;

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
    cam_config.highPerformanceRetrieveBuffer = true;
    camera.SetConfiguration( &cam_config );

    camera_index = index;
}

// The capture callback is a wrapper to emit the frameCaptured signal.
void CameraManager::imageGrabbed( FlyCapture2::Image * image ) {
    //thread Safe
    static QMutex mutex;
    mutex.lock();

    image_buffer->append( image );
    emit frameCaptured( image_buffer->front() );
    delete image_buffer->front();

    image_buffer->removeFirst();

    if(!is_capturing && image_buffer->empty())
        emit finishedCapturing();

    mutex.unlock();
    return;
}

bool CameraManager::stopCapture() {
    if ( !is_capturing )
        return false;


    grabber->stopCapturing();
    Error error = camera.StopCapture();
    if ( error != PGRERROR_OK ) {
        throw error;
        return false;
    }

    is_capturing = false;

    return image_buffer->empty();
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
    // TODO: ERRORS!
    grabber = new ImageGrabber( this );
    grabber->setCamera( &camera );
    connect( grabber, &ImageGrabber::imageCaptured, this, &CameraManager::imageGrabbed, Qt::QueuedConnection );
    connect( grabber, &ImageGrabber::finished, grabber, &ImageGrabber::deleteLater );
    grabber->start();

    is_capturing = true;
}
