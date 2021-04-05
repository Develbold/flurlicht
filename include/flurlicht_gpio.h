#ifndef FLURLICHT_GPIO_H
#define FLURLICHT_GPIO_H

#include <iostream>
#include <boost/log/trivial.hpp>
#include <memory>
#include <boost/thread/mutex.hpp>
#include "flurlicht_occupancy.h"
#include "leds.h"


extern "C" {
#include "rpi_ws281x_static/ws2811.h"
}

class FLURLICHT_GPIO
{
public:
    FLURLICHT_GPIO(std::shared_ptr<FLURLICHT_OCCUPANCY> occupancy);
//    bool initGPIO();

    typedef struct
    {
        bool current;
        bool next;
        bool blocked=false;
    } sensor_states_t;
    bool getSensorStates();
    void unblockStates();
    void flushStates();
    bool checkAnyBLocked();

private:
    //Sensor handling
    sensor_states_t Sensors_;
    bool states_ext_;

    std::chrono::high_resolution_clock::time_point last_trigger_time_;

    boost::mutex mutex_;

    std::shared_ptr<FLURLICHT_OCCUPANCY> occupancy_;

    //GPIO stuff
    const int PinFront_ = 14;
//    const int PinBack_ = 15;
    void handleGPIOCallback(int gpio, int level, uint32_t tick);
    static void handleGPIOCallbackExt(int gpio, int level, uint32_t tick,void *user);

    //misc tools
    void sleepPeriod(int period);
    const int cCoolOffPeriod_ = 5000;
    void updateStates(bool value);
};

#endif // FLURLICHT_GPIO_H
