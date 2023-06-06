#include "EspMQTTClient.h"
#include "HardwareSerial.h"
#include "ArduinoJson.h"

#define   BUF_LEN 256

HardwareSerial SerialPort(2); // use UART2

EspMQTTClient client(
  "SmartIndustriesMitch", //Wifi name
  "fontys123", //Wifi password
  "test.mosquitto.org",  // MQTT Broker server ip (test.mosquitto.org)
  "TestClient",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);

void setup() {
  Serial.begin(115200);
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);

  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overrited with enableHTTPWebUpdater("user", "password").
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true
}

void onConnectionEstablished() {
  client.subscribe("Garage/OnConnection", [](const String & payload) {
  });
}

void received() {
  if (SerialPort.available() > 0) {
    StaticJsonDocument<BUF_LEN> doc;
    String rc = SerialPort.readStringUntil('\n');
    client.publish("Garage/ParkingSpots", rc);

    DeserializationError error = deserializeJson(doc, rc);
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }
  }
}

void loop() {
  client.loop();
  received();
}