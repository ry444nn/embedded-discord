//
// IMPORTS
//
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "configs.h"

//
// INITS
//
AsyncWebServer server(80);

//
// VARIABLES
//
bool DEBUG = true;

/// @brief This is a handler for turning on and off the relays
/// @param relayId Is the GPIO pin allocated to the relay
/// @param relayValue Is the relay state either on - off
void relayManager(int relayId, String relayValue)
{
    if (relayValue == "on")
    {
        digitalWrite(relayId, LOW);
    }
    else if (relayValue == "off")
    {
        digitalWrite(relayId, HIGH);
    }
    else if (relayValue == "toggle")
    {
        digitalWrite(relayId, !digitalRead(relayId));
    }
}

/// @brief It is a handler for managing the relays which then sends it to the #relayManager
/// @param request
void relayHandler(AsyncWebServerRequest *request)
{
    bool relay1 = request->hasParam("relay1");
    bool relay2 = request->hasParam("relay2");

    if (relay1)
        relayManager(0, request->getParam("relay1")->value());

    if (relay2)
        relayManager(2, request->getParam("relay2")->value());
}

/// @brief Returns a status of the relay, HIGH or LOW. 1 = OFF, 0 = ON
/// @return State of relay
String relayStatus()
{
    bool relay1 = digitalRead(0);
    bool relay2 = digitalRead(2);
    return String(relay1) + "-" + String(relay2);
}

/// @brief Router for routing pages
void router()
{
    server.on("/relay", HTTP_POST, [](AsyncWebServerRequest *request)
              { relayHandler(request);
                          request->send(200, "text/plain", relayStatus()); });
    server.on("/status", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(200, "text/plain", relayStatus()); });

    server.begin();
}

/// @brief Setup
void setup()
{
    // SERIAL CONFIGS
    Serial.begin(115200);
    if (DEBUG == true)
        Serial.println("MAIN PROCESS RUNNING");

    // PIN OUTS
    pinMode(0, OUTPUT); // GPIO 0
    pinMode(2, OUTPUT); // GPIO 1

    delay(5000);

    // PIN CONFIGS
    digitalWrite(0, HIGH);
    digitalWrite(2, HIGH);

    // WIFI CONFIGS
    WiFi.mode(WIFI_AP_STA);
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.println("=");
    }

    WiFi.setHostname("RRE home");
    WiFi.softAP(s_name, s_pass);

    if (DEBUG == true)
    {
        Serial.println(WiFi.softAPIP());
        Serial.println(WiFi.localIP());
    }

    // ROUTER
    router();
}

void loop()
{
}
