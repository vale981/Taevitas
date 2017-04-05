#include "mainwindow.h"
#include "FlyCapture2.h"
#include <QApplication>

int main( int argc, char * argv[] ) {
    QApplication a( argc, argv );

    qRegisterMetaType<FlyCapture2::Error>();

    MainWindow w;
    w.show();

    return a.exec();
}
