// /*
// ESP-COAP Server
// * Renata Frenken: buggy, not working with ESP32
// */
// #include <Arduino.h>
// #include <WiFi.h>
// #include <coap_server.h>
// #include <coap-simple.h>
// #include <stdio.h>

// // CoAP server endpoint url callback
// void callback_light(coapPacket &packet, IPAddress ip, int port, int obs);

// coapServer coap;
// const int led = 2;
// // WiFi connection info
// const char *ssid = "Andre";
// const char *password = "Andre1818";

// // LED STATE
// bool LEDSTATE;

// // CoAP server endpoint URL
// void callback_light(coapPacket *packet, IPAddress ip, int port, int obs)
// {
//   Serial.println("light");
// #if 0
//   // send response
//   Serial.println(packet->payloadlen);

//   char p[packet->payloadlen + 1];

//   Serial.println(sizeof(p));

//   //printf("%c\n", packet->payload[1]);

//   memcpy(p, packet->payload, sizeof(packet->payload));

//   //p[packet->payload] = '\0';

//  // printf("%c\n", p[0]);

//   Serial.println(p[0]);

//   String message(p);

//   if (message.equals("0"))
//   {
//     digitalWrite(16,LOW);
//   }
//   else if (message.equals("1"))
//   {
//     digitalWrite(16,HIGH);
//   }
//   char *light = (digitalRead(16) > 0)? ((char *) "1") :((char *) "0");

//    if(obs==1)
//     coap.sendResponse(light);
//    else
//     coap.sendResponse(ip,port,light);
// #endif
// }

// void callback_lightled(coapPacket *packet, IPAddress ip, int port, int obs)
// {
//   Serial.println("Lightled");
//   printf("obs\n");

//   // send response
//   // char pie[packet->payloadlen + 1];

//   //  for (int i = 0; i<packet->payloadlen+1; ++i) {
//   //    pie[i] = (char)packet->payload[i];
//   // }
//   printf("a\n, %d", obs);
//   // memcpy(p, packet->payload, packet->payloadlen);
//   // pie[packet->payloadlen] = '\0';

// #if 0
// String s = (char *) &packet->payload[0];
//   String message(p);

//   Serial.print("Message is : ");
//   Serial.println(p);

//   if (message.equals("0"))
//     LEDSTATE = false;
//   else if (message.equals("1"))
//     LEDSTATE = true;

//   if (LEDSTATE) {
//     digitalWrite(led, HIGH) ;
//     if(obs==1)
//      coap.sendResponse("1");
//      else
//     coap.sendResponse(ip, port, "1");

//     //coap.sendResponse("1");
//   } else {
//     digitalWrite(led, LOW) ;
//     if (obs==1)
//     coap.sendResponse("0");
//     else
//     coap.sendResponse(ip, port, "0");
//     //coap.sendResponse("0");
//   }
// #endif
// }

// void setup()
// {
//   yield();
//   // serial begin
//   Serial.begin(115200);

//   WiFi.begin(ssid, password);
//   Serial.println(" ");

//   // Connect to WiFi network
//   Serial.println();
//   Serial.println();
//   Serial.print("Connecting to ");
//   Serial.println(ssid);
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED)
//   {
//     // delay(500);
//     yield();
//     Serial.print(".");
//   }
//   Serial.println("");
//   Serial.println("WiFi connected");
//   // Print the IP address
//   Serial.println(WiFi.localIP());

//   // LED State
//   pinMode(2, OUTPUT);
//   digitalWrite(2, HIGH);
//   LEDSTATE = true;

//   pinMode(led, OUTPUT);
//   digitalWrite(led, HIGH);
//   LEDSTATE = true;

//   // add server url endpoints.
//   // can add multiple endpoint urls.

//   // coap.server(callback_light, "light");
//   coap.server(callback_lightled, "lightled");

//   // start coap server/client
//   printf("Start \n");
//   coap.start();
// }

// void loop()
// {
//   coap.loop();
//   delay(1000);
// }