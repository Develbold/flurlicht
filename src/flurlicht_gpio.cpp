#include "flurlicht_gpio.h"
#include <chrono>
#include <thread>
#include "pigpio/pigpio.h"
#include "flurlicht_tools.h"


using namespace std;


void FLURLICHT_GPIO::handleGPIOCallback(int gpio, int level, uint32_t tick)
{
    bool state=false;
    //decode the level to state
    if(gpio == PinFront_)
    {
        BOOST_LOG_TRIVIAL(info) << "change detected! front level: " << level;
    }
    else
    {
        BOOST_LOG_TRIVIAL(info) << "change detected! (unknown pin)";
    }

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
//        setSensorState(FRONT,state);
        updateStates(state);
    }
    else
    {
        BOOST_LOG_TRIVIAL(error) << "GPIO: unknown pin";
    }
}

void FLURLICHT_GPIO::handleGPIOCallbackExt(int gpio, int level, uint32_t tick, void *user)
{
    auto *mySelf = (FLURLICHT_GPIO *) user;

    mySelf->handleGPIOCallback(gpio, level, tick);
}

auto FLURLICHT_GPIO::initGPIO() -> bool
{
    BOOST_LOG_TRIVIAL(info) << "GPIO initialing";
    if(gpioInitialise()==PI_INIT_FAILED)
    {
        BOOST_LOG_TRIVIAL(error) << "GPIO init failed";
        return false;
    }
    //set mode of GPIO
    if(gpioSetMode(PinFront_, PI_INPUT) !=0)
    {
        BOOST_LOG_TRIVIAL(error) << "GPIO mode set failed";
        return false;
    }
    if(gpioSetPullUpDown(PinFront_,PI_PUD_DOWN) !=0)
    {
        BOOST_LOG_TRIVIAL(error) << "GPIO set pulldown failed";
        return false;
    }

    //register Callbacks
    gpioSetAlertFuncEx(PinFront_, handleGPIOCallbackExt, (void *)this);
    updateStates(false);
    BOOST_LOG_TRIVIAL(info) << "GPIO initialized";
    return true;
}

FLURLICHT_GPIO::FLURLICHT_GPIO()
{
    last_trigger_time_= FLURLICHT_TOOLS::getTime();
}

bool FLURLICHT_GPIO::getSensorStates()
{
    bool buffer;
    mutex_.lock();
    buffer = states_ext_;
    mutex_.unlock();
    return buffer;

}

void FLURLICHT_GPIO::updateStates(bool value)
{
    if (value == true)
    {
//            BOOST_LOG_TRIVIAL(debug) << "reset last trigger time front";
            last_trigger_time_=FLURLICHT_TOOLS::getTime();
            mutex_.lock();
            states_ext_=true;
            mutex_.unlock();
    }
    else
    {
//            if (FLURLICHT_TOOLS::checkRenderTimeValid(last_trigger_time_,cCoolOffPeriod_))
//            {
//                BOOST_LOG_TRIVIAL(debug) << "clear trigger front";
                mutex_.lock();
                states_ext_=false;
                mutex_.unlock();
//            }
    }
}
