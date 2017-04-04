#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H


/*
   This Class is an abstraction over the FlyCapture2 API for handeling the connection to the camera and
   hiding the internals from the GUI code, to make reusability easier, although FlyCapture code is needed   outside.
*/

#include <QObject>
#include <QVector>
#include <QThread>
#include "FlyCapture2.h"
#include "imagegrabber.h"

class CameraManager : public QObject {
        Q_OBJECT

    public:
        explicit CameraManager( QObject * parent = 0 );
        ~CameraManager();

        // Connect camera from index. Once successfull it emits the cameraConnected signal.
        // Emits Error signal in case of an error.
        void connectCamera( int );

        // Starts capturing images. When an image has been captured, the signal frameCaptured is emited.
        // Throws FlyCapture2::Error
        void startCapture();
        void stopCapture();

        // NOTE: Maybe not needed.
        const FlyCapture2::Camera * getCamera() const {
            return &camera;
        }

        bool isConnected() {
            return camera.IsConnected();
        }

        // Get the number of connected cameras.
        unsigned int numCameras() {
            bus_mgr.GetNumOfCameras( &num_cameras );
            return num_cameras;
        }

        bool isCapturing() {
            return is_capturing;
        }

    private:
        FlyCapture2::Camera camera;
        FlyCapture2::FC2Config cam_config;
        FlyCapture2::BusManager bus_mgr;

        FlyCapture2::CallbackHandle handleC;
        FlyCapture2::CallbackHandle handleD;

        // Capture Thread
        ImageGrabber * grabber;

        // Status Variable
        bool is_capturing;

        unsigned int num_cameras;

        // Index of the current camera
        int camera_index;

        // GUID of the camera, which is currently being used
        FlyCapture2::PGRGuid camera_guid;

        // Event Handlers
        static void camConnectEvent( void * pParameter, unsigned int serialNumber );
        static void camDisconnectEvent( void * pParameter, unsigned int serialNumber );

    signals:
        void frameCaptured( FlyCapture2::Image * image ) const;
        void cameraConnected();
        void cameraDisconnected( bool current );

        void captureError( FlyCapture2::Error err );
};

#endif // CAMERAMANAGER_H
