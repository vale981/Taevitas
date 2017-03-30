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
        const QList<QSerialPortInfo> &getPorts();
        bool isConnected() const {
            return port.isOpen();
        }

    signals:
        void dataRead( QByteArray data );

    public slots:
        // TODO: Maybe Remove
        // returns False if the port is not open
        bool selectPort( const QSerialPortInfo &info );
        bool selectPort( const QString &portName );
        bool selectPort( const int index );

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
        void write( QByteArray data );

        int lastBuff;

    private slots:
        void handleRead();
};

#endif // SERIALCOMMUNICATOR_H
