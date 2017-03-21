#include "cameramanager.h"
#include <QDebug>
#include <QMutex>

using namespace FlyCapture2;

CameraManager::CameraManager(QObject *parent) : QObject(parent), num_cameras {0}, is_capturing {false} {
}

CameraManager::~CameraManager() {
	stopCapture();
	camera.Disconnect();
}

void CameraManager::connectCamera(unsigned int index) {
	// Don't connect twice.
	if(camera_index == index)
		return;

	if(camera.IsConnected())
		camera.Disconnect();
	
	qDebug() << "Connecting to camera: " << index << '\n';	
	Error error; // general purpose error object
	
	// get PGRGuid of the Camera
	BusManager bus_mgr;
	error = bus_mgr.GetCameraFromIndex(index, &camera_guid);
	if(error != PGRERROR_OK) {
		throw error;
		return;
	}

	// connectCamera
	error = camera.Connect(&camera_guid);
	if(error != PGRERROR_OK) {
		throw error;
		return;
	}

    // Do not drop frames! //TODO Flexible Buffer size
    cam_config = FlyCapture2::FC2Config();
    cam_config.grabMode = GrabMode::BUFFER_FRAMES;
    cam_config.numBuffers= 50;
    cam_config.highPerformanceRetrieveBuffer = true;
	camera_index = index;

    camera.SetConfiguration(&cam_config);
}

// The capture callback is a wrapper to emit the frameCaptured signal.
void CameraManager::captureCallback(FlyCapture2::Image* image, const void *camManager) {
    QMutex mutex;
    mutex.lock();

    if(camManager) {
        static_cast<const CameraManager*>(camManager)->frameCaptured(image);
    }
    qDebug() << "here";

    mutex.unlock();
    return;
}

void CameraManager::stopCapture() {
	if(!is_capturing)
		return;

	Error error;
	error = camera.StopCapture();

	if(error != PGRERROR_OK) {
		throw error;
		return;
	}

	is_capturing = false;
}

void CameraManager::startCapture() {
	// Don't capture twice!
	if(is_capturing)
		return;

	// Just a wrapper for the PTGrey method. Let all the errors be generated by the FlyCapture method.
	// TODO: Evtl try to connect to first camera...
	Error error;
	error = camera.StartCapture(captureCallback, this);

	if(error != PGRERROR_OK) {
		throw error;
		return;
	}

	is_capturing = true;
}

