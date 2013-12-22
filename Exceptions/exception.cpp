#include "exception.h"

Exception::Exception(QString message)
{
    this->message = message;
}

QString Exception::ToString()
{
    return this->message;
}

QString Exception::GetMessage()
{
    return this->message;
}

