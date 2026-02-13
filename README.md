# Arduino Voice Recognition and Discord connection

This project was a simple hobby project, that let me control my home lights via Discord or even voice recognition. Though, voice recognition i really never used the integration with Discord was very fun and useful.

## How to use

### Embedded Code

I've provided two examples for esp32 and esp8266 that you can implement on your own esp. Make sure to set all the right pins and your good to go! Upload the code via platformio.

### Bot code

Create your own `bot/config.json` where you put the discord developer bot token. Once done, simply run the code on a laptop or another device like a raspy and use slash commands from discord to control everything

```json
{
  "token": "YOUR TOKEN",
  "clientId": "",
  "guildId": ""
}
```

remember to run `node deploy-commands.js` and then `node index.js`

### Voice commands

Install the required python dependencies via

```bash
pip install speechrecognition pyaudio requests
```

pyaudio is generally a bit tricky to install, i would advice following their own documentation.
better yet create a venv and install your package their.

### API Requests

#### ESP32

1. GET / - Serves the Web Interface

Returns the index.html file from LittleFS for the web interface.

2. POST `/relay` - Control Relays

Accepts query/form parameters to control relays:

`relay1` - Value for relay 1
`relay2` - Value for relay 2

Example request:

```bash
curl -X POST "http://<ESP32_IP>/relay?relay1=ON&relay2=OFF"
```

#### ESP8266

POST `/relay` - Control relays

```bash
curl -X POST "http://<ESP8266_IP>/relay?relay1=on&relay2=off"
```

Returns status like "0-1" (relay1 ON, relay2 OFF)

GET `/status` - Check relay states

```bash
curl "http://<<ESP8266_IP>/status"
```

Returns "1-0" format (1=OFF, 0=ON)
