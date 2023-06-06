#ifndef __RFIDH__
#define __RFIDH__

#include "Arduino.h"
#include <SPI.h>
#include <MFRC522.h>

/*
Link for the library:
https://randomnerdtutorials.com/security-access-using-mfrc522-rfid-reader-with-arduino/
*/

class RFID
{
private:
    /* data */
public:
    RFID(/* args */);
    ~RFID();

    int ReadTag();
};

#endif