#ifndef CONTAINER_H
#define CONTAINER_H
#include <string>
#include <exception>
#include <QDataStream>
#include "container_global.h"

/**
 * @brief The Container class
 * Class represents data exchanged by server and client
 * There is no magic around here
 */
class CONTAINERSHARED_EXPORT Container
{
    int id;
    std::string name;

public:
    Container ()
    { }

    Container(int id, std::string name);

    Container(const Container &);

    Container &operator=(const Container &);

    int getId() const;

    const std::string &getName() const;

    void setName(const std::string &);

    void setId(int id);

    virtual ~Container()
    { }

    friend QDataStream & operator<<(QDataStream &, const Container &);

    friend QDataStream & operator>>(QDataStream &, Container &);
private:
    void swap(Container &other);

};

class CorruptedContainerException: public std::exception
{
    std::string message;
public:
    CorruptedContainerException(const std::string &);
    virtual ~CorruptedContainerException() throw()
    { }
    const char *what() const noexcept override;
};


QDataStream & operator<<(QDataStream &, const Container &);

QDataStream & operator>>(QDataStream &, Container &);

#endif // CONTAINER_H
