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

    // init GPIO, Events States
    events_ = std::make_shared<FLURLICHT_EVENTS>();
    Gpio_ = std::make_unique<FLURLICHT_GPIO>(events_);
    Gpio_->initGPIO();
    setNextState(ST_OFF);
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
    FLURLICHT_GPIO::sensor_states_t SensorBuffer = Gpio_->getSensorStates();
    States StateBuffer;
    States CurrentState = getCurrentState();
    bool AnimationBuffer = getAnimationState();

    //after all input data is collected free the locks
    events_->unlockAll();

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
    else if (CurrentState == ST_ANIMATION && AnimationBuffer == false)
    {
        StateBuffer = ST_ON;
    }
//    else if (CurrentState == ST_ANIMATION && AnimationBuffer == false && SensorBuffer.front == false && SensorBuffer.back == false)
//    {
//        StateBuffer = ST_OFF;
//    }
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

//return if state is valid based on if mutex is locked
bool flurlicht::checkStateValid()
{
    if(events_->checkAnyLocked())
    {
        //BOOST_LOG_TRIVIAL(debug) << "current state unvalid";
        return false;
    }
    else
    {
        //BOOST_LOG_TRIVIAL(debug) << "current state still valid";
        return true;
    }
}

void flurlicht::handleONState()
{
//    while(checkStateValid())
//    {
        sleepPeriod(10000);
//    }
    BOOST_LOG_TRIVIAL(info) << "finished ON state";
}

void flurlicht::handleOFFState()
{
    LEDs_->playAnimation(ANIMATION::fades_t::FADE_OUT);
    while(checkStateValid())
    {
        sleepPeriod(25);
    }
    BOOST_LOG_TRIVIAL(info) << "finished OFF state";
}

//finsih this state directly after animation
void flurlicht::handleANIMATIONState()
{
    LEDs_->playAnimation(ANIMATION::fades_t::FADE_IN);
    BOOST_LOG_TRIVIAL(info) << "finished ANIMATION state";
}

void flurlicht::handleERRORState()
{
    BOOST_LOG_TRIVIAL(info) << "finished ERROR state";
}

void flurlicht::sleepPeriod(int period)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(period));
}

bool flurlicht::getAnimationState()
{
    return LEDs_->getAnimationRunning();
}
