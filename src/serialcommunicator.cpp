#include "serialcommunicator.h"

SerialCommunicator::SerialCommunicator( QObject * parent ) : QObject( parent ), port( this ), lastBuff { 0 } {}

const QList<QSerialPortInfo> &SerialCommunicator::getPorts() {
    ports = QSerialPortInfo::availablePorts();
    return ports;
}

bool SerialCommunicator::selectPort( const QSerialPortInfo &info ) {
    port.setPort( info );
    bool open = port.isOpen();
    if ( open ) {
        emit connected();
    }

    return open;
}

// Overload just searches for the port.
bool SerialCommunicator::selectPort( const QString &portName ) {
    for ( QSerialPortInfo info : ports ) {
        if ( info.portName() == portName ) {
            return selectPort( info );
            break;
        }
    }

    return false;
}

// TODO: Maybe Inline
bool SerialCommunicator::selectPort( const int index ) {
    return selectPort( ports.at( index ) );
}

// TODO: Maybe Different
void SerialCommunicator::write( QByteArray data ) {
    if ( !port.isOpen() )
        return;

    port.write( data.append( '\n' ) );
}
