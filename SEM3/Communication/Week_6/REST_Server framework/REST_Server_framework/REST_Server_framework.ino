#include "WiFi.h"
#include "WebServer.h"
#include "ESPmDNS.h"

const char* ssid = "ssid";
const char *password = "pass";

int LED = 2;
int state = LOW;

WebServer server(80);

// Serving Hello world
void getHelloWorld() {
    server.send(200, "text/json", "{\"name\": \"Hello world\"}");
}


// Manage not found URL
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

// Read Hall Sensor
void readHallSensor()
{
  int val = hallRead();
  String valSensor = (String)val;
   
  String convertToText = valSensor;
  server.send(200, "text/json", convertToText);
}

// Read current led state
int readLEDSTate()
{
  String convertToText = printLedState();
  server.send(200, "text/json", convertToText);
}

// return string state of the LED
String printLedState()
{ 
   if (state == LOW)
   {
    return "LED state is LOW";
   }
   else if (state == HIGH) 
   {
    return "LED state is HIGH";
   }
}

// Here is an example/part of the function to set the LED value
void setBuiltInLed() {
  if(state == HIGH)
  {
    state = LOW;
    digitalWrite(LED, LOW);
  }
  else if(state == LOW)
  {
    state = HIGH;
    digitalWrite(LED, HIGH);
  }
}

void restServerRouting() {
    server.on("/", HTTP_GET, []() {
      server.send(200, F("text/html"), F("Welcome to the REST Web Server"));
          });
      server.on(F("/helloWorld"), HTTP_GET, getHelloWorld);
      
      server.on(F("/GETvalSensor"), HTTP_GET, readHallSensor);
      server.on(F("/GETvalLedGet"), HTTP_GET, readLEDSTate);
      server.on(F("/POSTled"), HTTP_POST, setBuiltInLed);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Start Wifi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
 
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Activate mDNS this is used to be able to connect to the server
  // with local DNS hostmane esp32.local
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

   // Set server routing
  restServerRouting();
  // Set not found response
  server.onNotFound(handleNotFound);
  // Start server
  server.begin();
  Serial.println("HTTP server started");

  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
