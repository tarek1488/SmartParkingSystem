# SmartParkingSystem
## Software Requirements
 - Python 3.8 or later
 - Arduino IDE

### Python installation
1) Download and install Python from [here](https://www.python.org/downloads/)

2) Creating a new environment:
```bash
$ cd path/to/your/project
$ python -m venv venv
```

3) Activate the environment(windows):
```bash
$ ./.venv\Scripts\Activate.ps1
```
## Installation

### Install required packages
```bash
$ cd Vision
$ pip install -r requirments.txt
```

### Arduino IDE setup for ESP and Firebase
1) Download and install Arduino IDE from [here](https://www.arduino.cc/en/software/)

2) Installing ESP8266 Board in Arduino IDE:
file -> preferences -> additional boards
Manager URL: insert the following URL -> https://arduino.esp8266.com/stable/package_esp8266com_index.json

3) tools -> Board -> board manager -> esp8266 community (latest version)

4) tools -> Esp8266 Boards -> select ( NodeMCU 1 (ESP – 12E module) )

5) tools -> library manage -> Install ArduinoJson (latest version)

6) tools -> library manage -> Install firebase Arduino client library for esp8266 and
esp 32 (latest version)

7) Download CP210x Universal Windows Driver from [here](https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers)

8) Right-click on the .inf file in the CP210x Universal Windows Driver downloaded folder, then click install

## Hardware Requirements
1) 2 NodeMCU esp8266
2) 2 Stepper motor
3) 2 ULN 2003 stepper motor driver
4) Jumpers
5) External Camera
6) 2 X 16 LCD
 
