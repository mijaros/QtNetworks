#include "server.h"
#include "socketthread.h"
#include <iostream>
Server::Server(qint16 port, QObject *parent) : QTcpServer(parent), port(port)
{
    qDebug() << "Server is created";
}

Server::~Server() {
    qDebug() << "Closing server";
}

void Server::start()
{
    if (!this->listen(QHostAddress::Any, port)) {
        qDebug() << "Server start failed";
        qDebug() << this->errorString();
        emit finished();
        exit(0);
    }
}

void Server::incomingConnection(qintptr handle)
{
    SocketThread *thread = new SocketThread(handle, parent()
                                            );

    thread->start();
}
