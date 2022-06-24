# flurlicht

Raspberry based controller for ws281x LEDs and PIR sensors. In combination with the Arduino based PIR sensor (see [arduino-PIR-MQTT-sensor](https://github.com/Develbold/arduino_pir_mqtt_ha)), this setup happily illuminates my hallway ("flur" in German) based on motion detection. Flurlicht randomly chooses between predefined animations to add some fun.


## Requirements
- compiled and installed Paho c++ (see [paho.mqtt.cpp](https://github.com/eclipse/paho.mqtt.cpp))
- Boost log & regex libs
- cmake

## Hints
- Running DietPi instead of Raspbian improves the animations. This setup is running on a ancient B+ model flawlessly
- After compilation, you can auto-start flurlicht via the included service file

## Open Tasks
- MORE animations
- make flurlicht available for Philips Hue
