/**
 * @file main.cpp
 * @authors
 * Sean-David Brokke (4208501)
 * Mitchell van ‘t Kruys (4058151​)
 * Nick Mulders (4523504​)
 * @brief 
 * @version 0.1
 * @date 2023-01-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "EntranceModule.h"
#include <WiFiClient.h>
#include "painlessMesh.h"
#include <Arduino.h>
#include "HardwareSerial.h"

HardwareSerial SerialPort(2);

/*---------------Prototype Functions--------------*/
void sendMessage();
void UpdateTotalAvailableParkingSpots();
void LCDProtocol();

/*-----------------------------*/
EntranceModule *entrance;

/*--------------------------------*/
String rx_message;
int TotalAvailableParkingSpots = 0;
int Numberofcarsentered;
int Numberofcarsparked;
uint32_t source;
const char *nodeIP;
String receiveMessage;
String receivedByte;

/*-----------------------*/
uint32_t NodeID;
bool MessageReturned = false;
String protocolMessage;
int protocolNumberofcarsparked;
int gateState = 0;

// test
bool calc_delay = false;
SimpleList<uint32_t> nodes;

IPAddress clusterIP;
Scheduler userScheduler; // to control your personal task
painlessMesh mesh;

Task taskSendMessage(TASK_SECOND * 1, TASK_FOREVER, &sendMessage);
Task checkNodeList(TASK_SECOND * 1, TASK_FOREVER, &UpdateTotalAvailableParkingSpots);


void ReceivedCallback(uint32_t from, String &msg)
{
  source = from;
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, receiveMessage);
  nodeIP = doc["NodeId"];
  TotalAvailableParkingSpots = doc["availableParkingspots"];
  Numberofcarsentered = doc["Numberofcarsentered"];
  Numberofcarsparked = doc["Numberofcarsparked"];

  /*-----------Receiving protocol for LCD display------------*/
  if (from == NodeID)
  {
    protocolNumberofcarsparked = doc["Numberofcarsparked"];
    protocolMessage = msg;
    MessageReturned = true;
  }
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
  entrance->SetTotalAvailableParkingSpots((int)((mesh.getNodeList().size()) * 5));
}

/*
* This function was meant to be a protocol for when the 
* entranceGate RFID tag was scanned. 
* The function would display the closest parking cluster 
* with available space.
* We did not end up using it since we did not have enough 
* time to debug it.
*/
void LCDProtocol()
{
  if (Numberofcarsentered < ((mesh.getNodeList().size()) * 5))
  {
    int pos = 0;
    for (uint32_t const &nodeID : mesh.getNodeList())
    {
      Serial.println(nodeID);
      NodeID = 0;
      NodeID = nodeID; // Goes wrong here for the second node

      pos++;
      delay(200); // Should be changed into a task 
      if (MessageReturned)
      {
        if (protocolNumberofcarsparked < 5)
        {
          entrance->DisplayLCD("Closest available parking spot at cluster : " + String(pos));
          break;
        }
      }
      MessageReturned = false;
    }
  }
  else
  {
    entrance->DisplayLCD("Garage full...");
  }
}

void sendMessage()
{
  char buffer[BUF_LEN];
  StaticJsonDocument<BUF_LEN> msg;
  msg["NodeId"] = mesh.getNodeId();
  msg["availableParkingspots"] = entrance->GetTotalAvailableParkingSpots();
  msg["Numberofcarsentered"] = entrance->GetNumCarsEntered();
  msg["Numberofcarsparked"] = entrance->GetNumCarsParked();
  serializeJson(msg, buffer);
  mesh.sendBroadcast(buffer);
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
  Serial.begin(115200);
  SerialPort.begin(115200, SERIAL_8N1, 16, 17);
  entrance = new EntranceModule(LCDSCLPIN, LCDSDAPIN, RFID_SDA_PIN_1, RFID_RST_PIN_1, RFID_SDA_PIN_2, RFID_RST_PIN_2);
  InitializeMeshCommunication(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT, WIFI_AP_STA, 6);
}


void loop()
{
  Numberofcarsentered = entrance->GetNumCarsEntered();
  entrance->CheckGate();

  entrance->DisplayLCD("Num cars :" + String(Numberofcarsentered));
  mesh.update();
}
