#include <Arduino.h>
#include <WiFi.h>
#include "EspMQTTClient.h"
#include "DHTesp.h"
#include "string.h"

#define DHTpin 13

DHTesp dht;

const int onBoardLED = 2;
const String *LEDIsTrue;
const char *mqtt_topic_temp = "nr_nodered/Temperature";
const char *mqtt_topic_hum = "nr_nodered/Humidity";
const char *mqtt_topic_switch = "nr_nodered/Switch";

EspMQTTClient client(
    "Andre",
    "Andre1818",
    "test.mosquitto.org", // MQTT Broker
    "",                   // Can be omitted if not needed
    "",                   // Can be omitted if not needed
    "andreESP",           // Client name that uniquely identify your device
    1883                  // The MQTT port, default to 1883. this line can be omitted
);

void LEDToggle(const String &LED)
{
  if (LED == "ON")
  {
    digitalWrite(onBoardLED, HIGH);
  }
  else if (LED == "OFF")
  {
    digitalWrite(onBoardLED, LOW);
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(onBoardLED, OUTPUT);
  // Optionnal functionnalities of EspMQTTClient :
  client.enableDebuggingMessages();                                          // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater();                                             // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overrited with enableHTTPWebUpdater("user", "password").
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline"); // You can activate the retain flag by setting the third parameter to true
  // SetUp of DHT22 Sensor
  dht.setup(DHTpin, DHTesp::DHT22);
}

// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
{
  // Subscribe to "nr_nodered/Switch" and display received message to Serial
  client.subscribe(mqtt_topic_switch, [](const String &payload)
                   {
  Serial.println(payload);
  LEDIsTrue = &payload;
  LEDToggle(*LEDIsTrue); });
}

void loop()
{
  client.loop();
  delay(dht.getMinimumSamplingPeriod());
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  // char payload[32];

  // snprintf(payload, sizeof(payload), "%.1f,%.1f", temperature, humidity);
  client.publish(mqtt_topic_temp, (String)temperature);
  client.publish(mqtt_topic_hum, (String)humidity);
  delay(1000);
}