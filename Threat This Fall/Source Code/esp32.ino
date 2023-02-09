#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "MyAP";
const char *password = "password";

WebServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");
  
  server.on("/", []() {
    String message = "Welcome to ESP32 Access Point Web Server This is Under construction : ( ";
    server.send(200, "text/plain", message);
  });
  server.begin();
}

void loop() {
  server.handleClient();
}
