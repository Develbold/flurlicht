#ifndef FLURLICHT_GPIO_H
#define FLURLICHT_GPIO_H

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

class FLURLICHT_GPIO
{
public:
    FLURLICHT_GPIO();
    bool initGPIO();
    typedef struct
    {
        bool front;
        bool back;
    } sensor_states_t;
    sensor_states_t getSensorStates();

private:
    //Sensor handling

    typedef enum {FRONT,BACK} sensor_dir_t;
    void setSensorState(sensor_dir_t dir, bool state, bool lock);
    sensor_states_t Sensors_;


    //GPIO stuff
    const int PinFront_ = 14;
    const int PinBack_ = 15;
    FLURLICHT_EVENTS Events_;
    void handleGPIOCallback(int gpio, int level, uint32_t tick);
    static void handleGPIOCallbackExt(int gpio, int level, uint32_t tick,void *user);

    //misc tools
    void sleepPeriod(int period);

};

#endif // FLURLICHT_GPIO_H
