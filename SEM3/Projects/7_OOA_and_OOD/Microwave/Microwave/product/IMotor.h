#ifndef IMOTOR_H
#define IMOTOR_H

class IMotor
{
public:
    virtual ~IMotor() {};

    virtual void SetPower(int power) = 0;
};

#endif
