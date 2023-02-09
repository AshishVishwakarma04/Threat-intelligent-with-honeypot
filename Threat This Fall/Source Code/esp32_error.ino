#include <WiFi.h>
#include <WiFiAP.h>
#include <WebServer.h>

WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Set ESP32 as an access point
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP32-AP", "password");

  // Get the IP address of the access point
  Serial.println(WiFi.softAPIP());

  server.on("/", [](){
    String html = "<html><body>";
    html += "<h1>Connected Clients:</h1><br>";
    html += "<table border='1' style='width:100%'>";
    html += "<tr><th>IP address</th><th>MAC address</th></tr>";
    for (int i = 0; i < WiFi.softAPgetStationNum(); i++) {
      IPAddress client_ip = WiFi.softAPClient(i).remoteIP();
      uint8_t *client_mac = WiFi.softAPClient(i).get_mac();
      html += "<tr><td>" + client_ip.toString() + "</td><td>";
      html += String(client_mac[0], HEX) + ":";
      html += String(client_mac[1], HEX) + ":";
      html += String(client_mac[2], HEX) + ":";
      html += String(client_mac[3], HEX) + ":";
      html += String(client_mac[4], HEX) + ":";
      html += String(client_mac[5], HEX) + "</td></tr>";
    }
    html += "</table></body></html>";
    server.send(200, "text/html", html);
  });

  server.begin();
}

void loop() {
  server.handleClient();
}
