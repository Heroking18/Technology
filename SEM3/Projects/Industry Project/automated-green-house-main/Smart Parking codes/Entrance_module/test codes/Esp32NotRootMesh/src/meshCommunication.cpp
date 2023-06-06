#include "meshCommunication.h"

// Lambda(for function pointers)
// have a Singleton to call in simple functions
//[count](string input){ serialprint some stuff}

MeshCommunication::MeshCommunication(TSTRING  name, TSTRING  password, Scheduler *userScheduler, uint16_t port, wifi_mode_t wifiMode, uint8_t maxconn)
{
  ///_mesh = new painlessMesh;

  this->_mesh = new painlessMesh;
  this->_mesh->init(name, password, userScheduler, port, wifiMode, maxconn);
  // this->_meshinit(name, password, userScheduler, port, maxconn);
  //  String received;
  uint32_t fromm;
  // auto rxMessage = variant.to<protocol::Single>();
  // String rxMessage = painlessmesh::protocol::Single::msg;
  //_userScheduler = userScheduler;
  _mesh->setDebugMsgTypes(ERROR | STARTUP); // set before init() so that you can see startup messages
  _mesh->init(name, password, userScheduler, port, WIFI_AP_STA, maxconn);
//   _mesh->onReceive(ReceivedCallback);
//   _mesh->onNewConnection(NewConnectionCallback);
//  _mesh->onChangedConnections(ChangedConnectionCallback);
//   _mesh->onNodeTimeAdjusted(NodeTimeAdjustedCallback);

  // This node and all other nodes should ideally know the mesh contains a root, so call this on all nodes
 // _mesh.setContainsRoot(true);

  // userScheduler->addTask(taskSendMessage);
  // taskSendMessage.enable();
}

// void ReceivedCallback(uint32_t from, String &msg)
// {

// }

// void NewConnectionCallback(uint32_t nodeId)
// {
//   Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
// }

// void ChangedConnectionCallback()
// {
//   Serial.printf("Changed connections\n");
// }

void ReceivedCallback(uint32_t from, String &msg)
{
  Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
}

void NewConnectionCallback(uint32_t nodeId)
{
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
}

auto changeConCallBAck = []()
{ Serial.printf("Changed connections\n"); };

void ChangedConnectionCallback()
{
  Serial.printf("Changed connections\n");
}

// void NodeTimeAdjustedCallback(int32_t offset) {
//     Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
// }

// String MeshCommunication::GetRxMessage()
// {
//   String msg = this->_rxMsg;
//   return msg;
// }

// uint32_t MeshCommunication::GetRxFrom()
// {
//   uint32_t msg = this->_rxFrom;
//   return msg;
// }

// uint32_t MeshCommunication::GetNodeID()
// {
//   return _mesh.getNodeId();
// }

// void MeshCommunication::SendBroadCast(TSTRING msg)
// {
//   _mesh.sendBroadcast(msg);
// }

// void MeshCommunication::Update()
// {
//   _mesh.update();
// }

// MeshCommunication::~MeshCommunication()
// {
// }
