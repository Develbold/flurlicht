# flurlicht

Raspberry based controller for ws281x LEDs in combination with PIR sensors. In combination with the arduino based PIR sensor (see [arduino-PIR-MQTT-sensor](https://github.com/Develbold/arduino_pir_mqtt_ha)), this setup hapilly illuminates my hallway ("flur" in german) based on motion detection. Flurlich randomly chooses between predefined animations to add some fun. 


## Requirements
- compiled and installed Paho c++ (see [paho.mqtt.cpp](https://github.com/eclipse/paho.mqtt.cpp))
- Boost log & regex libs
- cmake

## Hints
- Rinning DietPi instead of Raspbian improves the animations. This setup is running on a ancient B+ model flawlessly
- After compilation, you can autostart flurlicht via the included service file
