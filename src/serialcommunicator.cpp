#include "serialcommunicator.h"

SerialCommunicator::SerialCommunicator( QObject * parent ) : QObject( parent ), port( this ) {}

const QList<QSerialPortInfo> &SerialCommunicator::getPorts() {
    ports = QSerialPortInfo::availablePorts();
    return ports;
}

bool SerialCommunicator::selectPort( QSerialPortInfo &info ) {
    port.setPort( info );
    bool open = port.isOpen();
    if ( open ) {
        emit connected();
    }

    return open;
}

// Overload just searches for the port.
bool SerialCommunicator::selectPort( QString &portName ) {
    for ( QSerialPortInfo info : ports ) {
        if ( info.portName() == portName ) {
            return selectPort( info );
            break;
        }
    }
}
