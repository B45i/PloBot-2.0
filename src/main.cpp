#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid     = "PloBot 2.0";
const char *password = "helloworld";

ESP8266WebServer server(80);

void handleRoot() {
	server.send(200, "text/html",
		"<!DOCTYPE html>\n"
		"<html>\n"
    "<h1>\n"
    "Welcome to PloBot 2.0"
    "</h1>\n"
		"</html>"
	);
}

void handleText() {
  if(server.arg("text") == "") {
    Serial.println("No data received");
    server.send(200, "text/html", "No text received");
  }
  else {
    String textReceived = server.arg("text");
    Serial.print("Text: ");
    server.send(200, "text/html", "No text received: " + textReceived);
    Serial.println(textReceived);
  }
}

void setup() {
	delay(1000);

	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
	/* uncomment the passeord to make the AP closed */
	//WiFi.softAP(ssid, password);
	WiFi.softAP(ssid);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);

	server.on("/", handleRoot);
	server.on("/getText", handleText);

	server.begin();
	Serial.println("HTTP server started");
}

void loop() {
	server.handleClient();
}
