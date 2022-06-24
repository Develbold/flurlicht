#ifndef FLURLICHT_H
#define FLURLICHT_H

#include <iostream>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <memory>
#include <boost/thread/mutex.hpp>
#include "leds.h"
#include "flurlicht_gpio.h"
#include "flurlicht_occupancy.h"
#include "flurlicht_mqtt.h"

extern "C" {
#include "rpi_ws281x_static/ws2811.h"
}

class flurlicht
{
public:
    flurlicht();
    void run();

private:
    void readSensors();
    enum States
    {
        ST_OFF=0,
        ST_ANIMATION=2,
        ST_ON=1,
        ST_ERROR=-1
    };
    States getNextState();
    void setNextState(States next);
    States getCurrentState();
    States CurrentState_;
    void handleONState();
    void handleOFFState();
    void handleANIMATIONState();
    void handleERRORState();
    //Sensor handling
    bool getAnimationState();
    bool AnimationState_;

    //misc tools
    void sleepPeriod(int period);

    //led configuration
    const int cLEDCOunt_ = 240;
    const int cLEDPin_ = 18;
    const int cLEDStripeType_ = SK6812_STRIP;
    std::unique_ptr<LEDs> LEDs_;

    std::unique_ptr<FLURLICHT_GPIO> Gpio_;
    std::shared_ptr<FLURLICHT_OCCUPANCY> occupancy_;
    std::unique_ptr<FLURLICHT_MQTT> mqtt_;
};


#endif // FLURLICHT_H
