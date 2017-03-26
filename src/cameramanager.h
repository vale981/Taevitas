#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H


/* 
   This Class is an abstraction over the FlyCapture2 API for handeling the connection to the camera and 
   hiding the internals from the GUI code, to make reusability easier, although FlyCapture code is needed   outside.
*/

// TODO: implement camera arrival removal
#include <QObject>
#include <QVector>
#include <QThread>
#include "FlyCapture2.h"
#include "imagegrabber.h"

class CameraManager : public QObject
{
	Q_OBJECT
	
public:
	explicit CameraManager(QObject *parent = 0);
	~CameraManager();
	
	// Starts capturing images. When an image has been captured, the signal frameCaptured is emited.
	// Throws FlyCapture2::Error
	void startCapture();
    bool stopCapture();

	//TODO remove, if not needed
	const FlyCapture2::Camera* getCamera() const {
		return &camera;
	};

	bool isConnected() {
		return camera.IsConnected();
	}

	// Get the number of connected cameras.
	unsigned int numCameras() {
		FlyCapture2::BusManager bus_mgr;
		bus_mgr.GetNumOfCameras(&num_cameras);
		return num_cameras;
	};

	// Connect camera from index. Once successfull it emits the cameraConnected signal.
	// Emits Error signal in case of an error.
    void connectCamera(int);

	bool isCapturing() {
		return is_capturing;
	}

private:
    FlyCapture2::Camera camera;
    FlyCapture2::FC2Config cam_config;
	
	unsigned int num_cameras;

	// GUID of the camera, which is currently being used
	FlyCapture2::PGRGuid camera_guid;

	// Index of the current camera
    int camera_index;
	
	// State Variable
	bool is_capturing;

    QVector<FlyCapture2::Image *> *image_buffer;

    // Capture Thread
    ImageGrabber *grabber;

private slots:
    void imageGrabbed(FlyCapture2::Image *image);

signals:
    void frameCaptured(FlyCapture2::Image* image) const;
    void stopped() const;
};
	
#endif // CAMERAMANAGER_H

