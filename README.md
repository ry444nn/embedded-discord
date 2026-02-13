# Arduino Voice Recognition and Discord connection

This project was a simple hobby project, that let me control my home lights via Discord or even voice recognition. Though, voice recognition i really never used the integration with Discord was very fun and useful.

## How to use

### Embedded Code

I've provided two examples for esp32 and esp8266 that you can implement on your own esp. Make sure to set all the right pins and your good to go! Upload the code via platformio.

### Bot code

Create your own `bot/config.json` where you put the discord developer bot token. Once done, simply run the code on a laptop or another device like a raspy and use slash commands from discord to control everything

### Voice commands

Install the required python dependencies via

```bash
pip install speechrecognition pyaudio requests
```

pyaudio is generally a bit tricky to install, i would advice following their own documentation.
better yet create a venv and install your package their.
