#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H


/* 
   This Class is an abstraction over the FlyCapture2 API for handeling the connection to the camera and 
   hiding the internals from the GUI code, to make reusability easier, although FlyCapture code is needed   outside.
*/

// TODO: Exclude inline Implementation
// TODO: implement camera arrival removal
#include <QObject>
#include "FlyCapture2.h"

class CameraManager : public QObject
{
	Q_OBJECT
	
public:
	explicit CameraManager(QObject *parent = 0);
	~CameraManager();
	
	// Starts capturing images. When an image has been captured, the signal frameCaptured is emited.
	// Throws FlyCapture2::Error
	void startCapture();
	void stopCapture();
       
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
	void connectCamera(unsigned int);

	bool isCapturing() {
		return is_capturing;
	}

    FlyCapture2::Image& getCurrentImage() {
        return &current_image;
    }

    void setCurrentImage(FlyCapture2::Image image) {
        current_image.DeepCopy(image);
    }

private:
    FlyCapture2::Camera camera;
    FlyCapture2::FC2Config cam_config;
    FlyCapture2::Image current_image;
	
	unsigned int num_cameras;

	// GUID of the camera, which is currently being used
	FlyCapture2::PGRGuid camera_guid;

	// Index of the current camera
	unsigned int camera_index;
	
	// Just a littile wrapper function around the callback function for the camera capture to emit signals.
	static inline void captureCallback(FlyCapture2::Image*, const void*);

	// State Variable
	bool is_capturing;
	
signals:
	void frameCaptured(FlyCapture2::Image*) const;
};
	
#endif // CAMERAMANAGER_H

