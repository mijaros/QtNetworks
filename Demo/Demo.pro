TEMPLATE = subdirs

SUBDIRS += \
    Server \
    Client \
    Container

Server.depends = Container
Client.depends = Container
