#include "flurlicht_gpio.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/thread/mutex.hpp>

using namespace std;




FLURLICHT_GPIO::sensor_states_t FLURLICHT_GPIO::getSensorStates()
{
    sensor_states_t buffer;
    buffer.front =Sensors_.front;
    buffer.back = Sensors_.back;
    return buffer;

}

void FLURLICHT_GPIO::setSensorState(sensor_dir_t dir, bool state, bool lock=true)
{
        switch (dir)
        {
            case FRONT:
        {
            if (lock)
            {

                if (Events_.lockFront())
                {
                    Sensors_.front = state;
                }
            }
            else
                Sensors_.front = state;
            break;
        }
            case BACK:
        {
            if (lock)
            {
                if (Events_.lockBack())
                {
                    Sensors_.back = state;
                }
            }
            else
                Sensors_.back = state;
            break;
        }
        default:
            BOOST_LOG_TRIVIAL(debug) << "unknown dir ";
        }
}

void FLURLICHT_GPIO::handleGPIOCallback(int gpio, int level, uint32_t tick)
{
    bool state;
    //decode the level to state
    BOOST_LOG_TRIVIAL(info) << "movement detected! pin"<< gpio << " level: " << level;
    if (level==0)
    {
        state=false;
    }
    else if (level==1)
    {
        state=true;
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << "GPIO: unknown level";
    }
    if (gpio == PinFront_)
    {
        setSensorState(FRONT,state);
    }
    else if (gpio == PinBack_)
    {
        setSensorState(BACK,state);
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << "GPIO: unknown pin";
    }
}

void FLURLICHT_GPIO::handleGPIOCallbackExt(int gpio, int level, uint32_t tick, void *user)
{
    FLURLICHT_GPIO *mySelf = (FLURLICHT_GPIO *) user;

    mySelf->handleGPIOCallback(gpio, level, tick);
}

void FLURLICHT_GPIO::sleepPeriod(int period)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(period));
}

bool FLURLICHT_GPIO::initGPIO()
{
    BOOST_LOG_TRIVIAL(info) << "GPIO initialing";
    gpioInitialise();
    //set mode of GPIO
    gpioSetMode(PinFront_, PI_INPUT);
    gpioSetMode(PinBack_, PI_INPUT);
    //register Callbacks
//    gpioSetAlertFuncEx(PinFront_, handleGPIOCallbackExt, (void *)this);
    gpioSetAlertFuncEx(PinBack_, handleGPIOCallbackExt, (void *)this);
    setSensorState(FRONT,false,false);
    setSensorState(BACK,false,false);
    BOOST_LOG_TRIVIAL(info) << "GPIO initialized";
    return true;
}

FLURLICHT_GPIO::FLURLICHT_GPIO()
{
    setSensorState(FRONT,false,false);
    setSensorState(BACK,false,false);
}
