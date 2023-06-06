#ifndef ILIGHT_H
#define ILIGHT_H

class ILight
{
public:
    virtual ~ILight() {};

    virtual void On() = 0;
    virtual void Off() = 0;
};

#endif
