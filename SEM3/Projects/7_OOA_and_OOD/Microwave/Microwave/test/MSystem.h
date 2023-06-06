#ifndef MSYSTEM_H
#define MSYSTEM_H

#include "ISystem.h"

#include <gmock/gmock.h>

class MSystem : public ISystem
{
public:
    MOCK_METHOD1(SetTimer, void(int));
};

#endif
