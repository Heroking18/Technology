#include <painlessMesh.h>
#include <Arduino.h>
#include "HardwareSerial.h"

#define   MESH_PREFIX     "smartparkingcluster"
#define   MESH_PASSWORD   "fontys123"
#define   MESH_PORT       5555
#define   HOSTNAME "MQTT_Bridge"

HardwareSerial SerialPort(2); // use UART2

String rx_message;

void receivedCallback( const uint32_t &from, const String &msg ); 

Scheduler userScheduler;
painlessMesh  mesh;

void setup() {   
  Serial.begin(115200);
  SerialPort.begin(115200, SERIAL_8N1, 16, 17); 
  mesh.init( MESH_PREFIX, MESH_PASSWORD, MESH_PORT, WIFI_AP_STA, 6 );
  mesh.onReceive(&receivedCallback);

  mesh.setHostname(HOSTNAME);
  mesh.setRoot(true);
  mesh.setContainsRoot(true);
}

void loop() {
  mesh.update();
}

void receivedCallback( const uint32_t &from, const String &msg ) {
  Serial.printf("bridge: Received from %u msg=%s \n", from, msg.c_str());
  rx_message = msg.c_str();
  rx_message += '\n';
  SerialPort.print(rx_message);
}