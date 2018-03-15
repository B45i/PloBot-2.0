#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define WIFI_SSID "plobot"
#define WIFI_PASS "workinprogress"

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

void setupWiFi(){
    Serial.println("\nConnecting...");
    WiFi.begin(WIFI_SSID,WIFI_PASS);
    while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(500);
      }
     Serial.println("\nConnected : ");
     Serial.println(WiFi.localIP());
  }

void setup() {
	delay(1000);

	Serial.begin(115200);
	Serial.println();

	Serial.println("Setting Up WiFi..");
	setupWiFi();

	server.on("/", handleRoot);
	server.on("/getText", handleText);

	server.begin();
	Serial.println("HTTP server started");
}

void loop() {
	server.handleClient();
}
