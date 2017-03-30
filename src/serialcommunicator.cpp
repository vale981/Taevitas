#include "serialcommunicator.h"

SerialCommunicator::SerialCommunicator( QObject * parent ) : QObject( parent ), port( this ), lastBuff { 0 } {}

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

// TODO: Maybe Inline
bool SerialCommunicator::selectPort( int index ) {
    return selectPort( ports.at( index ) );
}

// TODO: Maybe Different
void SerialCommunicator::write( QString data ) {
    write( data.toUtf8().toStdString().c_str() );
}

void SerialCommunicator::write( char * data ) {
    if ( !port.isOpen() )
        return;

    port.write( data );
    port.write( '\n' );
}
