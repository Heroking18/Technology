#pragma once

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
    int SDApin = 5;
    int RstPin = 27;
    const int ipaddress[4] = {103, 97, 67, 25};
    //Variables
    byte nuidPICC[4] = {0, 0, 0, 0};
    MFRC522::MIFARE_Key key;
    MFRC522 rfid = MFRC522(SS_PIN, RST_PIN);

public:
    RFID(int, int, const int, byte, MIFARE_Key, rfid) = default;
    ~RFID();
    void readRFID(void);
    void printHex(byte *buffer, byte bufferSize);
    void printDec(byte *buffer, byte bufferSize);
};
