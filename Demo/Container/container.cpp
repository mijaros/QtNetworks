#include "container.h"
#include <QObject>
static QString head("MESSAGE_HEAD"), end__("MESSAGE_END");

using namespace std;
Container::Container(int id, string name): id(id), name(name)
{
}

Container::Container(const Container &other): id(other.id), name(other.name)
{
}

Container &Container::operator=(const Container &other)
{
    Container cop(other);
    this->swap(cop);
    return *this;
}


void Container::swap(Container &other)
{
    std::swap(this->id, other.id);
    std::swap(this->name, other.name);
}

int Container::getId() const
{
    return id;
}

const string &Container::getName() const
{
    return name;
}

void Container::setId(int id)
{
    this->id = id;
}

void Container::setName(const string &name)
{
    this->name = name;
}

QDataStream & operator<<(QDataStream &stream, const Container &object)
{
    stream << head
           << (qint32) object.id
           << QString::fromUtf8(object.name.c_str())
           << end__;
    return stream;
}

QDataStream & operator>>(QDataStream &stream, Container &object)
{
    QString gotHead, name, gotEnd;
    qint32 id;
    stream >> gotHead
            >> id
            >> name
            >> gotEnd;
    if (gotHead != head || gotEnd != end__) {
        throw CorruptedContainerException("Message does not have correct format");
    }
    object.id = id;
    object.name = name.toUtf8().toStdString();
    return stream;
}

CorruptedContainerException::CorruptedContainerException(const string &message): exception(), message(message)
{

}

const char * CorruptedContainerException::what() const noexcept
{
    return message.c_str();
}
