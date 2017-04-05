#include "mainwindow.h"
#include "recorder.h"
#include <QApplication>

int main( int argc, char * argv[] ) {
    QApplication a( argc, argv );

    qRegisterMetaType<RecorderError>();

    MainWindow w;
    w.show();

    return a.exec();
}
