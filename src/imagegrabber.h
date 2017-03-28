#ifndef IMAGEGRABBER_H
#define IMAGEGRABBER_H

#include <QThread>
#include "FlyCapture2.h"

class ImageGrabber : public QThread {
        Q_OBJECT

    public:
        ImageGrabber( QObject * parent = 0 ) : QThread( parent ) {}
        void run() Q_DECL_OVERRIDE;
        void setCamera( FlyCapture2::Camera * cam );

    private:
        bool capture;
        FlyCapture2::Camera * cam;

        FlyCapture2::Image tmp;

    signals:
        void imageCaptured( FlyCapture2::Image * image );

    public slots:
        void stopCapturing();
};

#endif // IMAGEGRABBER_H
