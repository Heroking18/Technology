#include <SPI.h>
#include "mcp2515_can.h"

const int spiCSPin = 10;
const int ledPin = 2;

mcp2515_can CAN(spiCSPin);

void setup()
{
    Serial.begin(115200);
    pinMode(ledPin,OUTPUT);

    while (CAN_OK != CAN.begin(CAN_500KBPS))
    {
        Serial.println("CAN BUS Init Failed");
        delay(100);
    }
    Serial.println("CAN BUS  Init OK!");
}


void loop()
{
    unsigned char len = 0;// read buffer length
    unsigned char buf[3]; // buffer to save the read byte

    if(CAN_MSGAVAIL == CAN.checkReceive())
    {
        CAN.readMsgBuf(&len, buf);

        unsigned long canId = CAN.getCanId();

        Serial.println("-----------------------------");
        Serial.print("Data from ID: 0x");
        Serial.println(canId, HEX);

        for(int i = 0; i<len; i++)
        {
            Serial.print(buf[i]);
            Serial.print("\t");
            if(buf[0] == 79 && buf[1] == 78) // ascii: 'O' is 79, 'N' is 78, message: ON
            {
                digitalWrite(ledPin, HIGH);
                delay(500);
            }
            else if(buf[0] == 79 && buf[1] == 70 && buf[2] == 70)// ascii: 'O' is 79, 'F' is 70, message: OFF
            {
                digitalWrite(ledPin, LOW);
                delay(500);
            }
        }
        Serial.println();
    }
}