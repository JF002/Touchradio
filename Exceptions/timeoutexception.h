#ifndef TIMEOUTEXCEPTION_H
#define TIMEOUTEXCEPTION_H
#include "exception.h"

class TimeoutException : public Exception
{
public:
    TimeoutException(QString message);
};

#endif // TIMEOUTEXCEPTION_H
