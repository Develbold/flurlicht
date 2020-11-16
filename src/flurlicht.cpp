#include "flurlicht.h"
#include "leds.h"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

flurlicht::flurlicht()
{
    BOOST_LOG_TRIVIAL(debug) << "calling flurlich constructor";
    LEDs LEDs_(cLEDPin_,cLEDCOunt_,cLEDStripeType_);

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
    while(true)
    {
        States NextState = getNextState();
        setNextState(NextState);
        switch (NextState)
        {
            case ST_OFF:
                BOOST_LOG_TRIVIAL(info) << "switched to OFF state";
                sleepPeriod(100);
            break;
            case ST_ON:
                BOOST_LOG_TRIVIAL(info) << "switched to ON state";
                sleepPeriod(100);
            break;
            case ST_ANIMATION:
                BOOST_LOG_TRIVIAL(info) << "switched to ANIMATION state";
                sleepPeriod(100);
            break;
            case ST_ERROR:
                BOOST_LOG_TRIVIAL(error) << "switched to ERROR state";
                sleepPeriod(1000);
            break;
            default:
                BOOST_LOG_TRIVIAL(error) << "switched to UNDEFINED state";
                sleepPeriod(1000);
        }
    }
    BOOST_LOG_TRIVIAL(info) << "finished loop";
}

flurlicht::States flurlicht::getNextState()
{
    SensorStates SensorBuffer = getSensorStates();
    States StateBuffer;
    States CurrentState = getCurrentState();
    bool AnimationBuffer = getAnimationState();

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
        StateBuffer = ST_ON;
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

flurlicht::SensorStates flurlicht::getSensorStates()
{
    SensorStates buffer;
    buffer.front =Sensors_.front;
    buffer.back = Sensors_.back;
    return buffer;

}

void flurlicht::setSensorStateFront(bool state)
{
    Sensors_.front = state;
}

void flurlicht::setSensorStateBack(bool state)
{
    Sensors_.back = state;
}

void flurlicht::setAnimationState(bool state)
{
    AnimationState_ = state;
}


void flurlicht::handleGPIOCallback(int gpio, int level, uint32_t tick)
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
    if (gpio == PinFront_)
    {
        setSensorStateFront(state);
    }
    else if (gpio == PinBack_)
    {
        setSensorStateBack(state);
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
    //gpioSetAlertFuncEx(PinFront_, handleGPIOCallbackExt, (void *)this);
    //gpioSetAlertFuncEx(PinBack_, handleGPIOCallbackExt, (void *)this);
    setSensorStateBack(true);
    setSensorStateFront(true);
    BOOST_LOG_TRIVIAL(info) << "GPIO initialized";
    return true;
}


bool flurlicht::getAnimationState()
{
    return this->AnimationState_;
}
