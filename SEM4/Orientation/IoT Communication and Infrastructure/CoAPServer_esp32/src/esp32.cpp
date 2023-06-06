#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <coap-simple.h>

const char *ssid = "Andre";
const char *password = "Andre1818";
const int led = 2;

// CoAP client response callback
void callback_response(CoapPacket &packet, IPAddress ip, int port);

// CoAP server endpoint url callback
void callback_light(CoapPacket &packet, IPAddress ip, int obs);

// UDP and CoAP class
// other initialize is "Coap coap(Udp, 512);"
// 2nd default parameter is COAP_BUF_MAX_SIZE(defaulit:128)
// For UDP fragmentation, it is good to set the maximum under
// 1280byte when using the internet connection.
WiFiUDP udp;
Coap coap(udp);

// LED STATE
bool LEDSTATE;

// CoAP server endpoint URL
void callback_light(CoapPacket &packet, IPAddress ip, int port)
{
  Serial.println("[Light] ON/OFF");

  // send response
  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = '\0';

  String message(p);

  if (message.equals("0"))
    LEDSTATE = false;
  else if (message.equals("1"))
    LEDSTATE = true;

  if (LEDSTATE)
  {
    digitalWrite(led, HIGH);
    coap.sendResponse(ip, port, packet.messageid, "1");
  }
  else
  {
    digitalWrite(led, LOW);
    coap.sendResponse(ip, port, packet.messageid, "0");
  }
}

void callback_lightled(CoapPacket &packet, IPAddress ip, int obs)
{
  Serial.println("Lightled");
  printf("obs\n");

  // send response
  // char pie[packet.payloadlen + 1];

  // for (int i = 0; i < packet.payloadlen + 1; ++i)
  // {
  //   pie[i] = (char)packet.payload[i];
  // }
  printf("a\n, %d", obs);
  // memcpy(pie, packet.payload, packet.payloadlen);
  // pie[packet.payloadlen] = '\0';

#if 0
String s = (char *) &packet->payload[0];
  String message(p);

  Serial.print("Message is : ");
  Serial.println(p);

  if (message.equals("0"))
    LEDSTATE = false;
  else if (message.equals("1"))
    LEDSTATE = true;

  if (LEDSTATE) {
    digitalWrite(led, HIGH) ;
    if(obs==1)
     coap.sendResponse("1");
     else
    coap.sendResponse(ip, port, "1");

    // coap.sendResponse("1");
  } else {
    digitalWrite(led, LOW) ;
    if (obs==1)
    coap.sendResponse("0");
    else
    coap.sendResponse(ip, port, "0");
    // coap.sendResponse("0");
  }
#endif
}

// CoAP client response callback
void callback_response(CoapPacket &packet, IPAddress ip, int port)
{
  Serial.println("[Coap Response got]");

  char p[packet.payloadlen + 1];
  memcpy(p, packet.payload, packet.payloadlen);
  p[packet.payloadlen] = '\0';

  Serial.println(p);
}

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // LED State
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  LEDSTATE = true;

  // add server url endpoints.
  // can add multiple endpoint urls.
  // exp) coap.server(callback_switch, "switch");
  //      coap.server(callback_env, "env/temp");
  //      coap.server(callback_env, "env/humidity");
  Serial.println("Setup Callback Light");
  coap.server(callback_light, "light");
  coap.server(callback_lightled, "lightled");

  // client response callback.
  // this endpoint is single callback.
  Serial.println("Setup Response Callback");
  coap.response(callback_response);

  // start coap server/client
  coap.start();
}

void loop()
{
  delay(1000);
  coap.loop();
}
/*
if you change LED, req/res test with coap-client(libcoap), run following.
coap-client -m get coap://172.20.10.8/light
coap-client -e "1" -m put coap://172.20.10.8/light
coap-client -e "0" -m put coap://172.20.10.8/light
*/
