#ifndef ISYSTEM_H
#define ISYSTEM_H

class ISystem
{
public:
    virtual ~ISystem() {};

    virtual void SetTimer(int ms) = 0;
};

#endif
