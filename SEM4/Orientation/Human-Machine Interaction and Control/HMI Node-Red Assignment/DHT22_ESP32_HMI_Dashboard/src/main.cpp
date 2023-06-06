#include <Arduino.h>
#include <WiFi.h>
#include "EspMQTTClient.h"
#include "DHTesp.h"

#define DHTpin 13

DHTesp dht;

EspMQTTClient client(
    "Andre",
    "Andre1818",
    "test.mosquitto.org", // MQTT Broker
    "",                   // Can be omitted if not needed
    "",                   // Can be omitted if not needed
    "andreESP",           // Client name that uniquely identify your device
    1883                  // The MQTT port, default to 1883. this line can be omitted
);

void setup()
{
  Serial.begin(115200);

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
  // Subscribe to "nr_workshop/test" and display received message to Serial
  // client.subscribe("nr_workshop/test", [](const String & payload) {
  // Serial.println(payload);
  // });
}

void loop()
{
  client.loop();
  delay(dht.getMinimumSamplingPeriod());
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  // char payload[32];

  // snprintf(payload, sizeof(payload), "%.1f,%.1f", temperature, humidity);
  client.publish("nr_nodered/Temperature", (String)temperature);
  client.publish("nr_nodered/Humidity", (String)humidity);
  delay(1000);
}