#include "imagegrabber.h"
#include <QDebug>

void ImageGrabber::run() {
    qDebug() << "Starting Capture.";
    capture = true;
    while ( true ) {
        tmp = new FlyCapture2::Image();
        stored_img = new FlyCapture2::Image();

        // TODO: Errors
        cam->RetrieveBuffer( tmp );

        qDebug() << "Image Grabbed!";

        stored_img->DeepCopy( tmp );
        emit imageCaptured( stored_img );
        delete tmp;
    }
}

void ImageGrabber::setCamera( FlyCapture2::Camera * cam ) {
    this->cam = cam;
}

void ImageGrabber::stopCapturing() {
    qDebug() << "Stopping Capture.";
    capture = false;

    delete tmp;
    delete stored_img;
}
