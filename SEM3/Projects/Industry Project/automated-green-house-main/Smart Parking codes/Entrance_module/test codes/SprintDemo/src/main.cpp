#include "ParkingCluster.h"
#include "EntranceModule.h"
#include <WiFiClient.h>
#include "painlessMesh.h"
#include <Arduino.h>
#include "HardwareSerial.h"

/*---------------Communication using mesh--------------*/
#define MESH_PREFIX "SPcluster"
#define MESH_PASSWORD "fontys123"
#define MESH_PORT 5555
#define BUF_LEN 256

/*---------------Change Pins--------------*/
#define REDLIGHTPIN 18
#define GREENLIGHTPIN 19
#define BLUELIGHTPIN 21
#define PRESSUREPIN 35
#define YELLOWBUTTONPIN 33
#define REDBUTTONPIN 23
#define BLUEBUTTONPIN 22
#define BLACKBUTTONPIN 15
#define LDRPIN 34

#define LCDSCLPIN 22
#define LCDSDAPIN 21
#define RFIDSDAPIN 3
#define RFIDRSTPIN 5
#define RESERVERFIDSDAPIN 4
#define RESERVERFIDRSTPIN 4

/*-----------------------------*/
String rx_message;
int TotalAvailableparkingSpots = 0;
HardwareSerial SerialPort(2);
/*---------------Prototype Functions--------------*/
void sendMessage();
void UpdateTotalAvailableParkingSpots();

/*-----------------------------*/
ParkingCluster *cluster = nullptr;
EntranceModule *entrance;
String msg;
int TotalAvailableParkingSpots;
IPAddress clusterIP;
uint32_t source;
String receiveMessage;
String receivedByte;
const char *nodeIP;
int Numberofcarsentered;
int Numberofcarsparked;
int pos;
Scheduler userScheduler; // to control your personal task
painlessMesh mesh;

unsigned long previousTime = 0;
unsigned long previousFirstTime = 0;

Task taskSendMessage(TASK_MILLISECOND * 500, TASK_FOREVER, &sendMessage);
Task checkNodeList(TASK_SECOND * 1, TASK_ONCE, &UpdateTotalAvailableParkingSpots);

void PinSetup()
{
  pinMode(REDLIGHTPIN, OUTPUT);
  pinMode(GREENLIGHTPIN, OUTPUT);
  pinMode(BLUELIGHTPIN, OUTPUT);
  pinMode(PRESSUREPIN, INPUT);
  pinMode(LDRPIN, INPUT);
}

IPAddress getlocalIP()
{
  return IPAddress(mesh.getStationIP());
}

void ReceivedCallback(uint32_t from, String &msg)
{
  // Serial.println("Received message");
  source = from;
  receiveMessage = msg;

  if (msg == "ReturnCarsParked")
  {
    Serial.println("received ReturnCarsParked");

    char buffer[BUF_LEN];
    StaticJsonDocument<BUF_LEN> msg;

    msg["NodeIP"] = clusterIP.toString();
    msg["availableParkingspots"] = cluster->GetTotalAvailableParkingSpotsInGarage();
    msg["Numberofcarsentered"] = cluster->GetNumCarsEntered();
    msg["Numberofcarsparked"] = cluster->GetNumCarsParked();
    serializeJson(msg, buffer);

    mesh.sendSingle(from, buffer);
    return;
  }

  DynamicJsonDocument doc(2048);
  deserializeJson(doc, receiveMessage);
  nodeIP = doc["NodeIP"];
  TotalAvailableParkingSpots = doc["availableParkingspots"];
  Numberofcarsentered = doc["Numberofcarsentered"];
  Numberofcarsparked = doc["Numberofcarsparked"];

  // Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
}


void NewConnectionCallback(uint32_t nodeId)
{
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
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
  cluster->SetTotalAvailableParkingSpotsInCluster((int)((mesh.getNodeList().size() + 1) * 5));
  Serial.println("cluster modules :" + String(mesh.getNodeList().size() + 1));
  Serial.println("Parking spaces :" + String((mesh.getNodeList().size() + 1) * 5));
  Serial.println("Parking spaces in class :" + String(cluster->GetTotalAvailableParkingSpotsInGarage()));
}

void sendMessage()
{
  char buffer[BUF_LEN];
  StaticJsonDocument<BUF_LEN> msg;
  // Serial.println("Sending...");
  msg["NodeIP"] = clusterIP.toString();
  msg["availableParkingspots"] = cluster->GetTotalAvailableParkingSpotsInGarage();
  msg["Numberofcarsentered"] = cluster->GetNumCarsEntered();
  msg["Numberofcarsparked"] = cluster->GetNumCarsParked();
  serializeJson(msg, buffer);
  mesh.sendBroadcast(buffer);
  SerialPort.write(buffer);
  SerialPort.write('\n');
}

void InitializeMeshCommunication(String mesh_prefix, String mesh_password, Scheduler *scheduler, uint16_t mesh_port, wifi_mode_t mode, uint8_t max_connections)
{
  mesh.setDebugMsgTypes(ERROR | STARTUP); // set before init() so that you can see startup messages
  // mesh.getNodeList();
  mesh.init(mesh_prefix, mesh_password, scheduler, mesh_port, mode, max_connections);
  mesh.onReceive(&ReceivedCallback);
  mesh.onNewConnection(&NewConnectionCallback);
  mesh.onDroppedConnection(&DroppedConnectionCallback);

  mesh.setContainsRoot(true);
  mesh.getNodeList();
  userScheduler.addTask(taskSendMessage);
  userScheduler.addTask(checkNodeList);
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

  if (clusterIP != getlocalIP())
  {
    clusterIP = getlocalIP();
  }
  // entrance->AssertRFID();
}
