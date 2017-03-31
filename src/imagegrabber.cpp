#include "imagegrabber.h"
#include <QDebug>

void ImageGrabber::run() {
    qDebug() << "Starting Capture.";
    capture = true;
    FlyCapture2::Error err;

    while ( capture ) {
        FlyCapture2::Image * stored_img = new FlyCapture2::Image();

        err = cam->RetrieveBuffer( &tmp );

        if ( !capture ) {
            delete stored_img;
            return;
        }

        qDebug() << "Image Grabbed!";

        stored_img->DeepCopy( &tmp );
        emit imageCaptured( stored_img );
    }
}

void ImageGrabber::setCamera( FlyCapture2::Camera * cam ) {
    this->cam = cam;
}

void ImageGrabber::stopCapturing() {
    qDebug() << "Stopping Capture.";
    capture = false;
}
