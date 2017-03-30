#ifndef SERIALCOMMUNICATOR_H
#define SERIALCOMMUNICATOR_H
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>

class SerialCommunicator : public QObject {
        Q_OBJECT
    public:
        explicit SerialCommunicator( QObject * parent = 0 );

    public:
        const QList<QSerialPortInfo> &getPorts();
        bool isConnected() const {
            return port.isOpen();
        }

    public slots:
        // returns False if the port is not open
        bool selectPort( QSerialPortInfo &info );
        bool selectPort( QString &portName );

    signals:
        void connected();

    private:
        QSerialPort port;

        QList<QSerialPortInfo> ports;
};

#endif // SERIALCOMMUNICATOR_H
