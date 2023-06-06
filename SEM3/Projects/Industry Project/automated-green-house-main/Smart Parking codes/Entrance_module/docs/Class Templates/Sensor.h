#ifndef __SENSORH__
#define __SENSORH__
#include <cstddef>

class Sensor
{
private:
    
public:
    Sensor();
    ~Sensor();
    int readLDR();
 	int readPressure();
};

#endif

