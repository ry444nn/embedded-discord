//
// IMPORTS
//
#include <Arduino.h>
#include <EEPROM.h>
#include <WiFi.h>
#include <LittleFS.h>
#include <ESPmDNS.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "time.h"
#include <HTTPClient.h>
#include <ESP_Mail_Client.h>
#include "LittleFS.h"
#include "configs.h"

//
// INITS
//
AsyncWebServer server(80);

//
// VARIABLES
//
const char *esp8266 = "http://192.168.0.219/relay";

//
// REQUESTS
//
int httpRequestsPost(const char *url, const char *parameters)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;

        String fullURL = url + String("?") + parameters;
        http.begin(fullURL);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        int responseCode = http.POST(parameters);
        http.writeToStream(&Serial);
        http.end();
        return responseCode;
    }

    return 860;
}

// EEPROM

// ROUTER
void router()
{
    server.on("/relay", HTTP_POST, [](AsyncWebServerRequest *request)
              {
        String params;

        if (request->hasParam("relay1"))
            params += "relay1=" + request->getParam("relay1")->value();
        if (request->hasParam("relay2"))
            params += "&relay2=" + request->getParam("relay2")->value();

        httpRequestsPost(esp8266, params.c_str());
        request->send(200, "text/html", "OK"); });

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/index.html"); });

    server.begin();
}

//
// MAIN
//
void setup()
{
    // SERIAL CONFIGS
    Serial.begin(115200);
    Serial.println("=== CODE RUNNING ===");

    // LITTLE FS
    if (!LittleFS.begin())
    {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }

    // WIFI CONFIGS
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print("=");
        delay(500);
    }

    Serial.println(WiFi.localIP());

    delay(500);

    router();
}

void loop()
{
}
