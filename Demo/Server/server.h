#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QThread>

/**
 * @brief The Server class
 * This server is infinite loop which waits for new connection from client
 */
class Server : public QTcpServer
{
    Q_OBJECT
    qint16 port;
public:
    explicit Server(qint16 port, QObject *parent = 0);

    /**
     * @brief start Method starts infinite loop
     */
    void start();

    ~Server();

protected:

    /**
     * @brief incomingConnection Method is evoked when new connection is established
     * Method starts new thread which handles communication with client
     * @param handle socket descriptor assigned to new connection
     */
    void incomingConnection(qintptr handle) override;
signals:

    /**
     * @brief finished Signal emited when the server was closed by error
     */
    void finished();
};

/**
 * @brief The Controler class
 * This class handles stdin and reads commands from stdin
 * The only valid command is quit which ends the application
 */
class Controler : public QThread {
    Q_OBJECT
public:

    Controler(QObject *parent = 0): QThread(parent)
    { }

    virtual ~Controler() {

    }

    void run() override;
};

#endif // SERVER_H
