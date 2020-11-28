#ifndef FLURLICHT_H
#define FLURLICHT_H

#include <iostream>
#include <boost/log/trivial.hpp>
#include <memory>
#include "leds.h"
extern "C" {
#include <pigpio/pigpio.h>
#include "rpi_ws281x/ws2811.h"
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
    //Sensor handling
    struct SensorStates
    {
        bool front;
        bool back;
    };
    SensorStates Sensors_;
    SensorStates getSensorStates();
    void setSensorStateFront(bool state);
    void setSensorStateBack(bool state);
    bool getAnimationState();
    //void setAnimationState(bool state);
    bool AnimationState_;

    //GPIO stuff
    bool initGPIO();
    void handleGPIOCallback(int gpio, int level, uint32_t tick);
    static void handleGPIOCallbackExt(int gpio, int level, uint32_t tick,void *user);
    const int PinFront_ = 14;
    const int PinBack_ = 15;
    //misc tools
    void sleepPeriod(int period);

    //led configuration
    const int cLEDCOunt_ = 240;
    const int cLEDPin_ = 18;
    const int cLEDStripeType_ = SK6812_STRIP;
    std::unique_ptr<LEDs> LEDs_;

};

#endif // FLURLICHT_H
