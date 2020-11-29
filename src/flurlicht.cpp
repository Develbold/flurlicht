#include "flurlicht.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/thread/mutex.hpp>

using namespace std;

flurlicht::flurlicht()
{
    BOOST_LOG_TRIVIAL(debug) << "calling flurlich constructor";
    LEDs_ = make_unique<LEDs>(cLEDPin_,cLEDCOunt_,cLEDStripeType_);

    // init GPIO and States
    Sensors_.back = false;
    Sensors_.front = false;
    setNextState(ST_OFF);
    initGPIO();
    BOOST_LOG_TRIVIAL(debug) << "finished flurlicht constructor";
}



void flurlicht::run()
{
    BOOST_LOG_TRIVIAL(info) << "entered flurlicht loop";
    if (LEDs_->returnWorkingState())
    {
        while(true)
        {
            BOOST_LOG_TRIVIAL(debug) << "getting next state";
            States NextState = getNextState();
            setNextState(NextState);
            switch (NextState)
            {
                case ST_OFF:
                    BOOST_LOG_TRIVIAL(info) << "switched to OFF state";
                    handleOFFState();
                break;
                case ST_ON:
                    BOOST_LOG_TRIVIAL(info) << "switched to ON state";
                    handleONState();
                break;
                case ST_ANIMATION:
                    BOOST_LOG_TRIVIAL(info) << "switched to ANIMATION state";
                    handleANIMATIONState();
                break;
                case ST_ERROR:
                    BOOST_LOG_TRIVIAL(error) << "switched to ERROR state";
                    handleERRORState();
                break;
                default:
                    BOOST_LOG_TRIVIAL(error) << "switched to UNDEFINED state";
                    sleepPeriod(1000);
            }
        }
    }
    else
    {
        BOOST_LOG_TRIVIAL(info) << "LED state bad, aborting";
    }

    BOOST_LOG_TRIVIAL(info) << "finished loop";
}

flurlicht::States flurlicht::getNextState()
{
    SensorStates SensorBuffer = getSensorStates();
    States StateBuffer;
    States CurrentState = getCurrentState();
    bool AnimationBuffer = getAnimationState();

    //after all input data is collected free the locks
    Events_.unlockAll();

    BOOST_LOG_TRIVIAL(debug) << "switching state absed on: STATE:" << CurrentState <<
                                ", FRONT:" << SensorBuffer.front<<
                                ", BACK:" << SensorBuffer.back<<
                                ", ANIMATION:" << AnimationBuffer;

    //TODO: Refactor
    if (CurrentState == ST_OFF && SensorBuffer.front == false && SensorBuffer.back == false)
    {
        StateBuffer = ST_OFF;
    }
    else if (CurrentState == ST_OFF && (SensorBuffer.front == true || SensorBuffer.back == true))
    {
        StateBuffer = ST_ANIMATION;
    }
    else if (CurrentState == ST_ANIMATION && AnimationBuffer == true)
    {
        StateBuffer = ST_ANIMATION;
    }
    else if (CurrentState == ST_ANIMATION && AnimationBuffer == false && (SensorBuffer.front == true || SensorBuffer.back == true))
    {
        StateBuffer = ST_ON;
    }
    else if (CurrentState == ST_ANIMATION && AnimationBuffer == false && SensorBuffer.front == false && SensorBuffer.back == false)
    {
        StateBuffer = ST_OFF;
    }
    else if (CurrentState == ST_ON && (SensorBuffer.front == true || SensorBuffer.back == true))
    {
        StateBuffer = ST_ON;
    }
    else if (CurrentState == ST_ON && (SensorBuffer.front == false && SensorBuffer.back == false))
    {
        StateBuffer = ST_OFF;
    }
    else
    {
        StateBuffer = ST_ERROR;
    }


    return StateBuffer;
}

void flurlicht::setNextState(flurlicht::States next)
{
    CurrentState_ = next;
}

flurlicht::States flurlicht::getCurrentState()
{
    return CurrentState_;
}

bool flurlicht::checkStateValid()
{
    return Events_.checkAnyLocked();
}

void flurlicht::handleONState()
{
    if (checkStateValid())
    {
        sleepPeriod(5000);
    }
}

void flurlicht::handleOFFState()
{
    if (checkStateValid())
    {
        LEDs_->playAnimation(ANIMATION::fades_t::FADE_OUT);
    }
}

void flurlicht::handleANIMATIONState()
{
    if (checkStateValid())
    {
        LEDs_->playAnimation(ANIMATION::fades_t::FADE_IN);
    }
}

void flurlicht::handleERRORState()
{

}

flurlicht::SensorStates flurlicht::getSensorStates()
{
    SensorStates buffer;
    buffer.front =Sensors_.front;
    buffer.back = Sensors_.back;
    return buffer;

}

void flurlicht::setSensorState(sensor_dir_t dir, bool state)
{
        switch (dir)
        {
            case FRONT:
        {
                if (Events_.lockFront())
                {
                    Sensors_.front = state;
                }
                break;
        }
            case BACK:
        {
                if (Events_.lockBack())
                {
                    Sensors_.back = state;
                }
            break;
        }
        default:
            BOOST_LOG_TRIVIAL(debug) << "unknown dir ";
        }
}

void flurlicht::handleGPIOCallback(int gpio, int level, uint32_t tick)
{
    bool state;
    //decode the level to state
    BOOST_LOG_TRIVIAL(info) << "movement detected! pin"<< gpio << " level: " << level;
    if (level==0)
    {
        //state=false;
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

void flurlicht::handleGPIOCallbackExt(int gpio, int level, uint32_t tick, void *user)
{
    flurlicht *mySelf = (flurlicht *) user;

    mySelf->handleGPIOCallback(gpio, level, tick);
}

void flurlicht::sleepPeriod(int period)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(period));
}

bool flurlicht::initGPIO()
{
    BOOST_LOG_TRIVIAL(info) << "GPIO initialing";
    gpioInitialise();
    //set mode of GPIO
    gpioSetMode(PinFront_, PI_INPUT);
    gpioSetMode(PinBack_, PI_INPUT);
    //register Callbacks
    gpioSetAlertFuncEx(PinFront_, handleGPIOCallbackExt, (void *)this);
    gpioSetAlertFuncEx(PinBack_, handleGPIOCallbackExt, (void *)this);
    setSensorState(FRONT,false);
    setSensorState(BACK,false);
    BOOST_LOG_TRIVIAL(info) << "GPIO initialized";
    return true;
}


bool flurlicht::getAnimationState()
{
    return LEDs_->getAnimationRunning();
}
