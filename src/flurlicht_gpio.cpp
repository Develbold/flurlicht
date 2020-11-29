#include "flurlicht_gpio.h"
#include <chrono>
//#include <flurlicht_gpio.h>
#include <thread>


using namespace std;




FLURLICHT_GPIO::sensor_states_dirs_t FLURLICHT_GPIO::getSensorStates()
{
    return Sensors_.current;

}

void FLURLICHT_GPIO::unblockStates()
{
    Sensors_.blocked_back=false;
    Sensors_.blocked_front=false;
}

bool FLURLICHT_GPIO::checkAnyBLocked()
{
    if(Sensors_.blocked_back==true||Sensors_.blocked_front==true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void FLURLICHT_GPIO::flushStates()
{
    Sensors_.current.front = Sensors_.next.front;
    Sensors_.current.back = Sensors_.next.back;
}

void FLURLICHT_GPIO::setSensorState(sensor_dir_t dir, bool state, bool lock=true)
{
        switch (dir)
        {
            case FRONT:
        {
            if (lock)
            {

                if (!Sensors_.blocked_front)
                {
                    Sensors_.current.front = state;
                    Sensors_.blocked_front =true;
                }
                else
                {
                    Sensors_.next.front = state;
                }
            }
            else
                Sensors_.current.front = state;
            break;
        }
            case BACK:
        {
            if (lock)
            {
                if (!Sensors_.blocked_back)
                {
                    Sensors_.current.back = state;
                    Sensors_.blocked_back =true;
                }
                else
                {
                    Sensors_.next.back = state;
                }
            }
            else
                Sensors_.current.back = state;
            break;
        }
        default:
            BOOST_LOG_TRIVIAL(debug) << "unknown dir ";
        }
}

void FLURLICHT_GPIO::handleGPIOCallback(int gpio, int level, uint32_t tick)
{
    bool state=false;
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

bool FLURLICHT_GPIO::initGPIO()
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
    setSensorState(FRONT,false,false);
    setSensorState(BACK,false,false);
    BOOST_LOG_TRIVIAL(info) << "GPIO initialized";
    return true;
}

//FLURLICHT_GPIO::FLURLICHT_GPIO(std::shared_ptr<FLURLICHT_EVENTS> events)
FLURLICHT_GPIO::FLURLICHT_GPIO()
{
    //Events_ = events;
    setSensorState(FRONT,false,false);
    setSensorState(BACK,false,false);
    unblockStates();
}
