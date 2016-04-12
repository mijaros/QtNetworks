#include <QCoreApplication>
#include "server.h"
#include <iostream>
#include <QThread>


void Controler::run() {
    std::string command;
    while (1) {
        std::cin >> command;
        if (command == "quit") {
            break;
        } else {
            std::cout << "Unknown command " << command << std::endl;
        }
    }
    exit(0);
}

int main(int argc, char *argv[])
{
    QCoreApplication application(argc, argv);

    Server server((qint16) 8081, &application); //create new server
    server.start(); //start new server
    std::cout << "Started" << std::endl;

    Controler controller(&application); //initialize command controller
    QObject::connect(&controller, SIGNAL(finished()), &application, SLOT(quit())); //connect signal from controller
    QObject::connect(&server, SIGNAL(finished()), &application, SLOT(quit()));
    controller.start(); //start controller
    return application.exec(); //start application event loop
}
