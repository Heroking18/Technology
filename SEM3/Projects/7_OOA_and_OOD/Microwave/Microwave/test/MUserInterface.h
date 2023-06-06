#ifndef MUSERINTERFACE_H
#define MUSERINTERFACE_H

#include "IUserInterface.h"

#include <gmock/gmock.h>

class MUserInterface : public IUserInterface
{
public:
    MOCK_CONST_METHOD0(Ping, void());
    MOCK_CONST_METHOD0(GetRequestedPower, int());
    MOCK_METHOD0(StartClock, void());
    MOCK_METHOD0(StopClock, void());
};

#endif
