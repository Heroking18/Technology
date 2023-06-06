#ifndef MLIGHT_H
#define MLIGHT_H

#include "ILight.h"

#include <gmock/gmock.h>

class MLight : public ILight
{
public:
    MOCK_METHOD0(On, void());
    MOCK_METHOD0(Off, void());
};

#endif
