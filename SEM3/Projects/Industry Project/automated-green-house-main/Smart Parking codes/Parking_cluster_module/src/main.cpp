/**
 * @file main.cpp
 * @authors
 * Sean-David Brokke (4208501)
 * Mitchell van ‘t Kruys (4058151​)
 * Daniel García López (4976215​)
 * Nick Mulders (4523504​)
 * @brief 
 * @version 0.1
 * @date 2023-01-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "ParkingCluster.h"
#include "painlessMesh.h"
#include "Arduino.h"
#include "HardwareSerial.h"
/*---------------Prototype Functions--------------*/
void sendMessage();
void UpdateTotalAvailableParkingSpots();

/*-----------------------------*/
ParkingCluster *cluster;
HardwareSerial SerialPort(2);
/*--------------------------------*/
String rx_message;
int TotalAvailableParkingSpots = 0;
int Numberofcarsentered;
int Numberofcarsparked;
uint32_t NodeId;
uint32_t source;
String receiveMessage;
String receivedByte;
/*-----------------------*/
bool MessageReturned = false;
String protocolMessage;
int protocolNumberofcarsparked;

Scheduler userScheduler; // to control your personal task
painlessMesh mesh;

Task taskSendMessage(TASK_SECOND * 1, TASK_FOREVER, &sendMessage);
Task checkNodeList(TASK_SECOND * 1, TASK_FOREVER, &UpdateTotalAvailableParkingSpots);

void PinSetup()
{
  pinMode(REDLIGHTPIN, OUTPUT);
  pinMode(GREENLIGHTPIN, OUTPUT);
  pinMode(BLUELIGHTPIN, OUTPUT);
}

void ReceivedCallback(uint32_t from, String &msg)
{
  if (msg == "ReturnCarsParked")
  {
    Serial.println("received ReturnCarsParked");

    char buffer[BUF_LEN];
    StaticJsonDocument<BUF_LEN> msg;

    msg["NodeId"] = mesh.getNodeId();
    msg["availableParkingspots"] = cluster->GetTotalAvailableParkingSpotsInGarage();
    msg["Numberofcarsentered"] = cluster->GetNumCarsEntered();
    msg["Numberofcarsparked"] = cluster->GetNumCarsParked();
    serializeJson(msg, buffer);

    mesh.sendSingle(from, buffer);
    return;
  }

  StaticJsonDocument <BUF_LEN> doc;
  deserializeJson(doc, receiveMessage);
  NodeId = doc["NodeId"];
  TotalAvailableParkingSpots = doc["availableParkingspots"];
  Numberofcarsentered = doc["Numberofcarsentered"];
  Numberofcarsparked = doc["Numberofcarsparked"];

  SerialPort.print(msg);
  SerialPort.write('\n');
}

void NewConnectionCallback(uint32_t nodeId)
{
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback()
{
  Serial.printf("Changed connections\n");
}

void DroppedConnectionCallback(uint32_t nodeId)
{
  Serial.printf("<-- EndHere: Dropped Connection, nodeId = %u\n", nodeId);
}

void nodeTimeAdjustedCallback(int32_t offset)
{
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(), offset);
}

void UpdateTotalAvailableParkingSpots()
{
  cluster->SetTotalAvailableParkingSpotsInCluster((int)((mesh.getNodeList().size()) * 5));
}

void sendMessage()
{

  char buffer[BUF_LEN];
  StaticJsonDocument<BUF_LEN> msg;
  msg["NodeId"] = mesh.getNodeId();
  msg["availableParkingspots"] = cluster->GetTotalAvailableParkingSpotsInGarage();
  msg["Numberofcarsentered"] = cluster->GetNumCarsEntered();
  msg["Numberofcarsparked"] = cluster->GetNumCarsParked();
  serializeJson(msg, buffer);
  mesh.sendBroadcast(buffer);
  SerialPort.write(buffer);
  SerialPort.write('\n');
  taskSendMessage.setInterval(TASK_SECOND * 2);
}

void InitializeMeshCommunication(String mesh_prefix, String mesh_password, Scheduler *scheduler, uint16_t mesh_port, wifi_mode_t mode, uint8_t max_connections)
{
  /*-----------------------------------------------------------------------------------------------*/
  mesh.setDebugMsgTypes(ERROR | STARTUP);
  mesh.init(mesh_prefix, mesh_password, scheduler, mesh_port, mode, max_connections);
  mesh.onReceive(&ReceivedCallback);
  mesh.onNewConnection(&NewConnectionCallback);
  mesh.onDroppedConnection(&DroppedConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.setContainsRoot(false);
  /*----------------------------------------------*/
  userScheduler.addTask(taskSendMessage);
  userScheduler.addTask(checkNodeList);
  /*-----------------------*/
  taskSendMessage.enable();
  checkNodeList.enable();
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
  cluster = new ParkingCluster(LDRPIN, PRESSUREPIN, REDLIGHTPIN, GREENLIGHTPIN, BLUELIGHTPIN, YELLOWBUTTONPIN, REDBUTTONPIN, BLUEBUTTONPIN, BLACKBUTTONPIN);
  InitializeMeshCommunication(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT, WIFI_AP_STA, 6);
}

void loop()
{
  cluster->ChangeLedColour();
  cluster->DetermineCarParked();
  mesh.update();
}