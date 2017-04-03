#include "mainwindow.h"
#include <QApplication>

int main( int argc, char * argv[] ) {
    qRegisterMetaType<FlyCapture2::Error>( "FlyCaptureError " );
    QApplication a( argc, argv );
    MainWindow w;
    w.show();

    return a.exec();
}
