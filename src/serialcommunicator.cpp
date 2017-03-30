#include "serialcommunicator.h"
#include "QDebug"

SerialCommunicator::SerialCommunicator( QObject * parent ) : QObject( parent ), port( this ), lastBuff { -1 } {
    connect( &port,  &QSerialPort::readyRead, this, &SerialCommunicator::handleRead );
}

SerialCommunicator::~SerialCommunicator() {
    port.close();
}

const QList<QSerialPortInfo> &SerialCommunicator::getPorts() {
    ports = QSerialPortInfo::availablePorts();
    return ports;
}

bool SerialCommunicator::selectPort( const QSerialPortInfo &info ) {
    port.close();
    port.setPort( info );

    bool open = port.open( QIODevice::ReadWrite );
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
    if ( index < 0 )
        return false;

    return selectPort( ports.at( index ) );
}

// TODO: Maybe Different
void SerialCommunicator::write( QByteArray data ) {
    if ( !port.isOpen() )
        return;

    port.write( data.append( '\n' ) );
}

void SerialCommunicator::handleRead() {
    emit dataRead( port.readAll() );
}
