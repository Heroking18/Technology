#include "meshCommunication.h"

// Lambda(for function pointers)
// have a Singleton to call in simple functions
//[count](string input){ serialprint some stuff}


// MeshCommunication::MeshCommunication(String name, String password, Scheduler *userScheduler, uint16_t port, uint16_t maxconn, String msg1)
// {
//   // _mesh.init() painlessMesh
//   // String received;
//   uint32_t fromm;
//   // auto rxMessage = variant.to<protocol::Single>();
//   // String rxMessage = painlessmesh::protocol::Single::msg;
//   //_userScheduler = userScheduler;
//   _mesh.setDebugMsgTypes(ERROR | STARTUP); // set before init() so that you can see startup messages
//   _mesh.init(name, password, userScheduler, port, WIFI_AP_STA, maxconn);
//   //_mesh.onReceive(ReceivedCallback(fromm,msg));
//   _mesh.onNewConnection(NewConnectionCallback);
//   _mesh.onChangedConnections(ChangedConnectionCallback);
//  // _mesh.onNodeTimeAdjusted(NodeTimeAdjustedCallback);

//   // This node and all other nodes should ideally know the mesh contains a root, so call this on all nodes
//   _mesh.setContainsRoot(true);

//   // userScheduler->addTask(taskSendMessage);
//   // taskSendMessage.enable();
// }

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
/*
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
  }}*/
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
