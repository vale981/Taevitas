#ifndef SERIALCOMMUNICATOR_H
#define SERIALCOMMUNICATOR_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>

class SerialCommunicator : public QObject {
        Q_OBJECT
    public:
        explicit SerialCommunicator( QObject * parent = 0 );
        ~SerialCommunicator();

        bool isConnected() const {
            return port.isOpen();
        }

        const QList<QSerialPortInfo> &getPorts();

    public slots:
        // returns False if the port is not open
        bool selectPort( const QSerialPortInfo &info );
        inline bool selectPort( const int index );

        // Signal Specific
        void sendRun() {
            write( "Run" );
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
        int lastBuff;

        void write( QByteArray data );

    private slots:
        void handleRead();

    signals:
        void dataRead( QByteArray data );
};

bool SerialCommunicator::selectPort( const int index ) {
    if ( index < 0 )
        return false;

    return selectPort( ports.at( index ) );
}

#endif // SERIALCOMMUNICATOR_H
