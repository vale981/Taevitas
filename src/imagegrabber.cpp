#include "imagegrabber.h"
#include <QDebug>

void ImageGrabber::run() {
    qDebug() << "Starting Capture.";
    capture = true;
    while(capture) {
        FlyCapture2::Image* tmp = new FlyCapture2::Image();
        FlyCapture2::Image* stored_img = new FlyCapture2::Image();

        cam->RetrieveBuffer(tmp);
        tmp->DeepCopy(stored_img);
        emit imageCaptured(stored_img);
    }
}

void ImageGrabber::setCamera(FlyCapture2::Camera *cam) {
    this->cam = cam;
}

void ImageGrabber::stopCapturing() {
   qDebug() << "Stopping Capture.";
   capture = false;
}

