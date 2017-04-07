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


// NOTE: Maybe Nicer
void SerialCommunicator::write( QByteArray data ) {
    if ( !port.isOpen() )
        emit portClosed();

    port.write( data.append( '\n' ) );
}

void SerialCommunicator::handleRead() {
    emit dataRead( port.readAll() );
}
