#include <QCoreApplication>
#include <container.h>
#include <QTcpSocket>
#include <iostream>
#include <QHostAddress>

#define PROMPT std::endl << ">>> "

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    std::string ipaddr;
    int port_number = 0;

    std::cout << "Write host address" << PROMPT;
    std::cin >> ipaddr;
    std::cout << "Write host port" << PROMPT;
    std::cin >> port_number;

    //Create a socket
    QTcpSocket soc(&a);
    soc.connectToHost(QHostAddress(QString(ipaddr.c_str())), port_number);
    if (!soc.waitForConnected()) { //handle error
        std::cerr << "Could not connect";
        return 0;
    }

    std::string message;
    int id = 0;

    std::cout << "Set the message to be sent" << PROMPT;
    std::cin >> message;
    std::cout << "Set id of message" << PROMPT;
    std::cin >> id;

    Container c(id, message); //Prepare data to sent
    QByteArray arr;
    QDataStream str(&arr, QIODevice::WriteOnly);

    str << c;
    soc.write(arr); //Send data
    soc.waitForBytesWritten();

    soc.waitForReadyRead(); //Wait for data to arrive
    QDataStream u(&soc);
    Container e;
    u >> e; //read data
    std::cout << e.getId() << " " << e.getName() << std::endl;
    soc.disconnectFromHost(); //end communication

    return 0;
}
