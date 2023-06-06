#ifndef _MESHCOMMUNICATION_
#define _MESHCOMMUNICATION_
#include <Arduino.h>
#include "painlessMesh.h"

#define BUF_LEN 256
// String received;
class MeshCommunication
{
private:
    /* data */
    // String _name;
    // String _password;
    // String _nodeId;
    painlessMesh *_mesh;
    static uint32_t _rxFrom;
    static String _rxMsg;
    // uint16_t _port;
    // uint8_t _maxconn;
    char _buffer[BUF_LEN];
    // Task *_taskSendMessage;
    /// Scheduler *_userScheduler;

public:
    MeshCommunication(TSTRING , TSTRING , Scheduler *, uint16_t, wifi_mode_t, uint8_t);
    // void Begin();
    String GetRxMessage();
    uint32_t GetRxFrom();

    uint32_t GetNodeID();
    void SendBroadCast(TSTRING msg);
    void Update();

    ~MeshCommunication();
};
void ReceivedCallback(uint32_t, String &);
void NewConnectionCallback(uint32_t);
void ChangedConnectionCallback();
void NodeTimeAdjustedCallback(int32_t);
// void SendMessage();
//  void ReceivedCallback(uint32_t, String &);
//  void NewConnectionCallback(uint32_t);
//  void ChangedConnectionCallback();
//  void NodeTimeAdjustedCallback(int32_t);

#endif