#include "Microwave.h"

#include <iostream>

Microwave::Microwave(ILight &light, IMotor &motor, ISystem &system, IUserInterface &ui)
    : currentState(STATE_IDLE), light(light), motor(motor), system(system), ui(ui)
{
}

States Microwave::HandleIdleState(Events ev)
{
    States result = STATE_IDLE;

    switch (ev)
    {
    case EV_START:
        // heating started with power
        result = STATE_HEATING;
        light.On();
        ui.StartClock();
        motor.SetPower(ui.GetRequestedPower());
        break;
    default:
        // ignored event, nothing to do here
        break;
    }

    return result;
}

void Microwave::HandleEvent(Events ev)
{
    switch (currentState)
    {
    case STATE_IDLE:
        currentState = HandleIdleState(ev);
        break;
    case STATE_HEATING:
        // possible situations during heating
        if (ev == EV_TIME_UP)
        {
            currentState = STATE_COOKING_COMPLETE;
        }
        else if (ev == EV_PAUSE)
        {
            currentState = STATE_PAUSED;
            ui.StopClock();
            ui.Ping();
        }
        break;
    case STATE_COOKING_COMPLETE:
        if (ev == EV_COOKING_COMPLETE)
        {
            currentState = STATE_IDLE;
            light.Off();
            ui.StopClock();
            ui.Ping();
        }
        break;
    case STATE_PAUSED:
        if (ev == EV_RESTART)
        {
            currentState = STATE_RESTARTED;
            ui.StartClock();
            ui.Ping();
        }
        else if (ev == EV_STOP)
        {
            currentState = STATE_COOKING_COMPLETE;
        }
        break;
    case STATE_RESTARTED:
        if (ev == EV_START)
        {
            currentState = STATE_HEATING;
        }

        break;

    default:
        std::cerr << "ERROR: illegal/unhandled state with number: " << currentState;
        break;
    };
}

States Microwave::getCurrentState()
{
    return currentState;
}
