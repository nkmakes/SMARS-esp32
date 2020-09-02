#include <Arduino.h>
#include "Arduino.h"
#include <ArduinoWebsockets.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <TB6612_ESP32.h>

#include "config.h"
#include "web.h"

/** ESP32 robot tank with wifi and one joystick web control sketch. 
    Based on SMARS modular robot project using esp32 and tb6612.
    https://www.thingiverse.com/thing:2662828
    for complete complete program: https://github.com/nkmakes/SMARS-esp32
    Made by nkmakes.github.io, August 2020.
 **/

Motor motor2 = Motor(AIN1, AIN2, PWMA, offsetA, STBY,5000 ,8,1 );
Motor motor1 = Motor(BIN1, BIN2, PWMB, offsetB, STBY,5000 ,8,2 );
 
using namespace websockets;
WebsocketsServer server;
AsyncWebServer webserver(80);

int LValue, RValue, commaIndex;

void setup()
{
  Serial.begin(9600);

  // Create AP
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // HTTP handler assignment
  webserver.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse_P(200, "text/html", index_html_gz, sizeof(index_html_gz));
    response->addHeader("Content-Encoding", "gzip");
    request->send(response);
  });

  // start server
  webserver.begin();
  server.listen(82);
  Serial.print("Is server live? ");
  Serial.println(server.available());
 
}
 
// handle http messages
void handle_message(WebsocketsMessage msg) {
  commaIndex = msg.data().indexOf(',');
  LValue = msg.data().substring(0, commaIndex).toInt();
  RValue = msg.data().substring(commaIndex + 1).toInt();
  motor1.drive(LValue);
  motor2.drive(RValue);
}
 
void loop()
{
  auto client = server.accept();
  client.onMessage(handle_message);
  while (client.available()) {
    client.poll();
  }
}