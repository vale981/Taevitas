#include "imagegrabber.h"
#include <QDebug>

void ImageGrabber::run() {
    qDebug() << "Starting Capture.";
    capture = true;
    while( true ) {
        FlyCapture2::Image* tmp = new FlyCapture2::Image();
        FlyCapture2::Image* stored_img = new FlyCapture2::Image();

        // TODO: Errors
        cam->RetrieveBuffer(tmp);

        if( !capture )
            return;

        qDebug() << "Image Grabbed!";

        stored_img->DeepCopy(tmp);
        emit imageCaptured(stored_img);
        delete tmp;
    }
}

void ImageGrabber::setCamera(FlyCapture2::Camera *cam) {
    this->cam = cam;
}

void ImageGrabber::stopCapturing() {
   qDebug() << "Stopping Capture.";
   capture = false;
}

