# Simple MQTT Sensor

A simple MQTT sensor project that publishes an analog value every 5 seconds.

## Prerequisites
1. Download and Install [**VSCode** Editor](https://code.visualstudio.com/Download).
    - *Optional:* Setup color theme (Beautiful UI).
    - *Optional:* Setup Icon theme (Material Icon Theme).
    - *Optional:* Setup Font (Monaco/Fira Code/JetBrains Mono).
    
2. Download and Install [**Python** 3.11](https://docs.platformio.org/en/latest/faq/install-python.html).

3. Download and Install [**Git**](https://www.atlassian.com/git/tutorials/install-git#windows). 

4. Within **VSCode** Extentions tab, find and install **PlatformIO IDE** extension.

![PlatformIO within VSCode Extensions](images/PlatformIO%20Extension.JPG)

## Build and Upload
1. Replace WiFi credentials at `WIFI_SSID` and `WIFI_PASS`
2. Connect the ESP32 to the computer.
3. From the lowbar, hit 'Upload' button.

![PlatformIO within VSCode Extensions](images/upload.JPG)

3. Wait until compilation and upload finishes.
4. Open Serial Monitor (The plug icon).

## MQTT Server
There are two options to work for an MQTT server: 
1. Connect to public server.
2. Connect to installed local server.

### Public Server
Public servers allow for quick demonstrations. 

You can switch to a public server by changing `MQTT_URL` in main.cpp file.

Because lots of people connect to and publish/subscribe to its topics, the user need to prepend at least one level topic to distinguish his path from others.

For that sake: assign your own Topic Level to `TOPIC_LEVEL` variable WITHOUT prepending or appending a topic separator `/`.

### Local Server

Install a local server (as mosquitto) in your system, thorough tutorials are available on the web, as [this](https://cedalo.com/blog/how-to-install-mosquitto-mqtt-broker-on-windows/).


After making sure the server works, and to facilitate working further, make the IP of server's machine as static, so it won't be changing across router reboots.

## How to visualize data sent? 
Install an MQTT Client that enables graphic view, and possible logging feature.

Instances of available MQTT Clients: 
- [MQTT-Explorer](https://mqtt-explorer.com/).
- [MQTTX](https://mqttx.app/).
- [MQTT Dash](https://play.google.com/store/apps/details?id=net.routix.mqttdash&hl=de).


Read more about MQTT Tools from [this link](https://github.com/hobbyquaker/awesome-mqtt?tab=readme-ov-file#visualization-dashboards).

