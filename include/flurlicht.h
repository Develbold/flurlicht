#ifndef FLURLICHT_H
#define FLURLICHT_H

#include <iostream>
#include <boost/log/trivial.hpp>
#include <memory>
#include <boost/thread/mutex.hpp>

#include "flurlicht_events.h"
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
    bool checkStateValid();
    void handleONState();
    void handleOFFState();
    void handleANIMATIONState();
    void handleERRORState();
    //Sensor handling
    struct SensorStates
    {
        bool front;
        bool back;
    };
    typedef enum {FRONT,BACK} sensor_dir_t;
    void setSensorState(sensor_dir_t dir, bool state);
    SensorStates Sensors_;
    SensorStates getSensorStates();
    bool getAnimationState();
    //void setAnimationState(bool state);
    bool AnimationState_;

    //GPIO stuff
    const int PinFront_ = 14;
    const int PinBack_ = 15;
    FLURLICHT_EVENTS Events_;
    bool initGPIO();
    void handleGPIOCallback(int gpio, int level, uint32_t tick);
    static void handleGPIOCallbackExt(int gpio, int level, uint32_t tick,void *user);

    //misc tools
    void sleepPeriod(int period);

    //led configuration
    const int cLEDCOunt_ = 240;
    const int cLEDPin_ = 18;
    const int cLEDStripeType_ = SK6812_STRIP;
    std::unique_ptr<LEDs> LEDs_;

};

#endif // FLURLICHT_H
