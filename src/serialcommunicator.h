#ifndef SERIALCOMMUNICATOR_H
#define SERIALCOMMUNICATOR_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>

class SerialCommunicator : public QObject {
        Q_OBJECT
    public:
        explicit SerialCommunicator( QObject * parent = 0 );
        explicit ~SerialCommunicator();

    public:
        const QList<QSerialPortInfo> &getPorts();
        bool isConnected() const {
            return port.isOpen();
        }

    public slots:
        // TODO: Maybe Remove
        // returns False if the port is not open
        bool selectPort( const QSerialPortInfo &info );
        bool selectPort( const QString &portName );
        bool selectPort( const int index );

        // Signal Specific
        void sendStart() {
            write( "Start" );
        }

        void sendHalt() {
            write( "Halt" );
        }

        void sendFast() {
            write( "Fast" );
        }

        void sendBuffer( int buff ) {
            if ( lastBuff != buff )
                write( QByteArray( "B" ) + QString::number( buff ).toUtf8() );
        }

    private:
        QSerialPort port;
        QList<QSerialPortInfo> ports;
        void write( QByteArray data );

        int lastBuff;
};

#endif // SERIALCOMMUNICATOR_H
