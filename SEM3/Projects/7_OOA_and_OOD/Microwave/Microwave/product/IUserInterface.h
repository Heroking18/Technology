#ifndef IUSERINTERFACE_H
#define IUSERINTERFACE_H

class IUserInterface
{
public:
    virtual ~IUserInterface() {};

    virtual void Ping() const = 0;
    virtual int GetRequestedPower() const = 0;
    virtual void StartClock() = 0;
    virtual void StopClock() = 0;
};

#endif
