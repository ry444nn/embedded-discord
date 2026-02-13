import speech_recognition as sr
import requests
import subprocess
import webbrowser

r = sr.Recognizer()
url = "https://open.spotify.com/playlist/37i9dQZF1DX5trt9i14X7j"
new = 2

def handler(audio):
    if "light" in audio and "on" in audio:
        requests.post("http://192.168.0.219/relay?relay2=on")
    elif "light" in audio and "off" in audio:
        requests.post("http://192.168.0.219/relay?relay2=off")
    elif "open" in audio and "code" in audio:
        subprocess.call("code")
    elif "open" in audio and "browser" in audio or "chrome" in audio:
        subprocess.call("google-chrome")
    elif "open" in audio and "postman" in audio:
        subprocess.call("postman")
    elif "mode" in audio and "programming" in audio or "coding" in audio:
        requests.post("http://192.168.0.219/relay?relay2=on")
        subprocess.call("code")
        webbrowser.get(using='google-chrome').open(url,new=new)

with sr.Microphone() as source:
    print("Speak:")
    r.adjust_for_ambient_noise(source)
    audio = r.listen(source)

try:
    handler(r.recognize_google(audio))
except sr.UnknownValueError:
    print("Could not understand audio")
except sr.RequestError as e:
    print("Could not request results; {0}".format(e))
