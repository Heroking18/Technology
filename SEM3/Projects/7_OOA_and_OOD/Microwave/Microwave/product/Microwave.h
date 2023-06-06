#ifndef MICROWAVE_H
#define MICROWAVE_H

#include "Events.h"
#include "States.h"
#include "ILight.h"
#include "IMotor.h"
#include "ISystem.h"
#include "IUserInterface.h"

class Microwave
{
public:
    Microwave(ILight &light, IMotor &motor, ISystem &system, IUserInterface &ui);

    void HandleEvent(Events ev);
    States HandleIdleState(Events ev);
    States getCurrentState();

private:
    States currentState;
    ILight &light;
    IMotor &motor;
    ISystem &system;
    IUserInterface &ui;
};

#endif
