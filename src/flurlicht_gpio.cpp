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
        BOOST_LOG_TRIVIAL(info) << "change detected! back level: " << level;
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
        updateStates(state,FRONT);
    }
    else if (gpio == PinBack_)
    {
        //setSensorState(BACK,state);
        updateStates(state,BACK);
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
    if(gpioSetMode(PinBack_, PI_INPUT) !=0)
    {
        BOOST_LOG_TRIVIAL(error) << "GPIO mode set failed";
        return false;
    }
    if(gpioSetPullUpDown(PinFront_,PI_PUD_DOWN) !=0)
    {
        BOOST_LOG_TRIVIAL(error) << "GPIO set pulldown failed";
        return false;
    }
    if(gpioSetPullUpDown(PinBack_,PI_PUD_DOWN) !=0)
    {
        BOOST_LOG_TRIVIAL(error) << "GPIO set pulldown failed";
        return false;
    }

    //register Callbacks
    gpioSetAlertFuncEx(PinFront_, handleGPIOCallbackExt, (void *)this);
    gpioSetAlertFuncEx(PinBack_, handleGPIOCallbackExt, (void *)this);
    updateStates(false,FRONT);
    updateStates(false,BACK);
    BOOST_LOG_TRIVIAL(info) << "GPIO initialized";
    return true;
}

FLURLICHT_GPIO::FLURLICHT_GPIO()
{
    last_trigger_time_front_= FLURLICHT_TOOLS::getTime();
    last_trigger_time_back_= FLURLICHT_TOOLS::getTime();
}

auto FLURLICHT_GPIO::getSensorStates() -> FLURLICHT_GPIO::sensor_states_dirs_t
{
    FLURLICHT_GPIO::sensor_states_dirs_t buffer;
    mutex_.lock();
    buffer = states_ext_;
    mutex_.unlock();
    return buffer;

}

void FLURLICHT_GPIO::updateStates(bool value, sensor_dir_t dir)
{
    if (value == true)
    {
        if (dir == sensor_dir_t::FRONT)
        {
//            BOOST_LOG_TRIVIAL(debug) << "reset last trigger time front";
            last_trigger_time_front_=FLURLICHT_TOOLS::getTime();
            mutex_.lock();
            states_ext_.front=true;
            mutex_.unlock();
        }
        else
        {
//            BOOST_LOG_TRIVIAL(debug) << "reset last trigger time back";
            last_trigger_time_back_=FLURLICHT_TOOLS::getTime();
            mutex_.lock();
            states_ext_.back=true;
            mutex_.unlock();
        }
    }
    else
    {
        if(dir == sensor_dir_t::FRONT)
        {
            if (FLURLICHT_TOOLS::checkRenderTimeValid(last_trigger_time_front_,cCoolOffPeriod_))
            {
//                BOOST_LOG_TRIVIAL(debug) << "clear trigger front";
                mutex_.lock();
                states_ext_.front=false;
                mutex_.unlock();
            }
        }
        else
        {
            if (FLURLICHT_TOOLS::checkRenderTimeValid(last_trigger_time_back_,cCoolOffPeriod_))
            {
//                BOOST_LOG_TRIVIAL(debug) << "clear trigger back";
                mutex_.lock();
                states_ext_.back=false;
                mutex_.unlock();
            }
        }

    }
}
