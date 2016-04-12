#include "socketthread.h"
#include <QDataStream>
#include <QHostAddress>
#include <iostream>
#include <container.h>

SocketThread::SocketThread(qintptr socket_ptr, QObject *parent) : QThread(parent), sock_ptr(socket_ptr)
{
    qDebug() << "Constructing new thread";

}

void SocketThread::run()
{
    socket = new QTcpSocket(NULL);
    socket->setSocketDescriptor(sock_ptr);
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()), Qt::DirectConnection);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readData()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(quit()), Qt::DirectConnection);
    const QHostAddress &connected = socket->peerAddress();
    qDebug()<< connected.toString();
    exec();
}

SocketThread::~SocketThread()
{
    qDebug() << "Quiting";
    delete socket;
}

void SocketThread::readData()
{
    qDebug() << "Reading data";
    QDataStream input(socket);
    Container data;
    input >> data;
    std::cout << data.getId() << " " << data.getName() << std::endl;

    Container c2(data);
    c2.setId(c2.getId()+1);
    c2.setName(c2.getName() + " Response");

    QByteArray array;
    QDataStream output(&array, QIODevice::WriteOnly);

    output << c2;
    socket->write(array);
}

void SocketThread::quit()
{
    exit(0);
}

