#include "painlessMesh.h"
#include "ArduinoJson.h"
#include <WiFiClient.h>

// PainlessMesh credentials
#define   MESH_PREFIX     "smartparkingcluster"
#define   MESH_PASSWORD   "fontys123"
#define   MESH_PORT       5555

//json stuff
#define BUF_LEN 256
String msg;
int maxAvailableparkingSpots;
int NumberOfCarsParked;
int NumberOfCarsEntered;

IPAddress clusterIP;

Scheduler userScheduler; // to control your personal task
painlessMesh  mesh;

// User stub
void sendMessage() ; // Prototype so PlatformIO doesn't complain

Task taskSendMessage( TASK_SECOND * 1 , TASK_FOREVER, &sendMessage );

IPAddress getlocalIP() {
  return IPAddress(mesh.getStationIP());
}

void sendMessage() {
  char buffer[BUF_LEN];
  StaticJsonDocument<BUF_LEN> msg;

  msg["NodeIP"] = String(getlocalIP());
  msg["availableParkingspots"] = maxAvailableparkingSpots;
  msg["Numberofcarsentered"] = NumberOfCarsEntered;
  msg["Numberofcarsparked"] = NumberOfCarsParked;
  serializeJson(msg, buffer);
  mesh.sendBroadcast(buffer);
  taskSendMessage.setInterval( random( TASK_SECOND * 2, TASK_SECOND * 5 ));
}

void receivedCallback( uint32_t from, String &msg ) {
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
  maxAvailableparkingSpots += 5;
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
  if(maxAvailableparkingSpots < 0){

    maxAvailableparkingSpots = 5;
  }else{
    maxAvailableparkingSpots -= 5;
  }
}

// void nodeTimeAdjustedCallback(int32_t offset) {
//     Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
// }

void setup() {
  Serial.begin(115200);
  mesh.setDebugMsgTypes( ERROR | STARTUP );

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT, WIFI_AP_STA, 6);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  //mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

  mesh.setContainsRoot(true); 

  userScheduler.addTask( taskSendMessage );
  taskSendMessage.enable();
  maxAvailableparkingSpots = 5;
  NumberOfCarsParked = 0;
  NumberOfCarsEntered = 0;
}

void loop() {
  // it will run the user scheduler as well
  mesh.update();
    if(clusterIP != getlocalIP()){
    clusterIP = getlocalIP();
  }
} 