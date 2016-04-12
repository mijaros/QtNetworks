#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>

/**
 * @brief The SocketThread class
 * This class represents handler of single connection to client.
 */
class SocketThread : public QThread
{
    Q_OBJECT

    qintptr sock_ptr;
    QTcpSocket *socket;

public:
    explicit SocketThread(qintptr socket_ptr, QObject *parent = 0);

    ~SocketThread();

    void run() override;

signals:

private slots:

    /**
     * @brief readData slot which is runned on readyRead signal from socket
     * This slot reads data from socket and then sends back response
     */
    void readData();

    /**
     * @brief quit slot which is runned on disconnected signal from socket
     * This slot ends the thread and emits signal finished (this behaviour is inherited from QThread)
     */
    void quit();


};

#endif // SOCKETTHREAD_H
