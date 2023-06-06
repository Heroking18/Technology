#include <Arduino.h>
#include "EspMQTTClient.h"
#include <string.h>

EspMQTTClient client(
    "C.V.Note9",          // Can be omitted if not needed
    "CORVI2020",          // Can be omitted if not needed
    "test.mosquitto.org", // MQTT Broker server ip
    "RobotClient69",      // Client name that uniquely identify your device
    1883                  // The MQTT port, default to 1883. this line can be omitted
);

#define SER2_RX 16
#define SER2_TX 17

String distance = "";
uint8_t set_point = 0;
const char *setpoint_topic = "group3robot/setpoint";
const char *distance_topic = "group3robot/distance";

void setup()
{
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, SER2_RX, SER2_TX);
  client.enableHTTPWebUpdater();
  client.enableDebuggingMessages();
}

void onConnectionEstablished()
{
  // client.subscribe(distance_topic, [](const String &topic, const String &payload) {});
  client.subscribe(setpoint_topic, [](const String &topic, const String &payload)
                   {
      set_point = payload.toInt();
      Serial2.write(set_point); });
}

void loop()
{
  client.loop();

  if (Serial2.available())
  {
    distance = Serial2.readStringUntil('\n');
    Serial.println(distance);
    distance.trim();
    client.publish(distance_topic, distance);
  }
}