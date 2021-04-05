#include "flurlicht.h"
#include "flurlicht_tools.h"
#include "flurlicht_gpio.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/creation_tags.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>

using namespace std;

flurlicht::flurlicht()
{
    BOOST_LOG_TRIVIAL(debug) << "calling flurlich constructor";
    occupancy_ = std::make_shared<FLURLICHT_EVENTS>();

    mqtt_ = std::make_unique<FLURLICHT_MQTT>(occupancy_);
    mqtt_->createSensorCallback("homeassistant/binary_sensor/0010fa6e384a/pir_front/state");
//    sleep(15);
    BOOST_LOG_TRIVIAL(debug) << "creating second callback";
    mqtt_->createSensorCallback("homeassistant/binary_sensor/0010fa6e384a/pir_back/state");

    sleep(120);
    LEDs_ = make_unique<LEDs>(cLEDPin_,cLEDCOunt_,cLEDStripeType_);

    Gpio_ = std::make_unique<FLURLICHT_GPIO>(occupancy_);
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
                    FLURLICHT_TOOLS::sleepPeriod(1000);
            }
        }
    }
    else
    {
        BOOST_LOG_TRIVIAL(info) << "LED state bad, aborting";
    }

    BOOST_LOG_TRIVIAL(info) << "finished loop";
}

auto flurlicht::getNextState() -> flurlicht::States
{
//    bool SensorBuffer = Gpio_->getSensorStates();
    bool SensorBuffer = occupancy_->getOccupancy();
    States CurrentState = getCurrentState();
    bool AnimationBuffer = getAnimationState();

    BOOST_LOG_TRIVIAL(debug) << "switching state based on: STATE:" << CurrentState <<
                                ", FRONT:" << SensorBuffer<<
                                ", ANIMATION:" << AnimationBuffer;

    //TODO: Refactor
    switch (CurrentState)
    {
    case ST_OFF:
        if(SensorBuffer == false)
        {
            return ST_OFF;
        }
        else
        {
            return ST_ANIMATION;
        }
        break;
    case ST_ANIMATION:
        if (AnimationBuffer)
        {
            return ST_ANIMATION;
        }
        else
        {
            return ST_ON;
        }
        break;
    case ST_ON:
        if (SensorBuffer == false)
        {
            return ST_OFF;
        }
        else
        {
            return ST_ON;
        }
        break;
    default:
        return ST_ERROR;
        break;
    }
}

void flurlicht::setNextState(flurlicht::States next)
{
    CurrentState_ = next;
}

auto flurlicht::getCurrentState() -> flurlicht::States
{
    return CurrentState_;
}

//return if state is valid based on if mutex is locked
auto flurlicht::checkStateValid(bool state) -> bool
{
//    bool buffer = Gpio_->getSensorStates();
    bool buffer = occupancy_->getOccupancy();
    return (buffer==state);
}

void flurlicht::handleONState()
{
//    while(checkStateValid())
//    {
        FLURLICHT_TOOLS::sleepPeriod(30000);
//    }
    BOOST_LOG_TRIVIAL(info) << "finished ON state";
}

void flurlicht::handleOFFState()
{
    LEDs_->playAnimation(LEDs::BLINK,ANIMATION::fades_t::FADE_OUT);
    while(checkStateValid(false))
    {
        FLURLICHT_TOOLS::sleepPeriod(100);
    }
    BOOST_LOG_TRIVIAL(info) << "finished OFF state";
}

//finsih this state directly after animation
void flurlicht::handleANIMATIONState()
{
    LEDs_->playAnimation(LEDs_->getRandomAnimation(),ANIMATION::fades_t::FADE_IN);
//    LEDs_->playAnimation(LEDs::SCANNER,ANIMATION::fades_t::FADE_IN);
    BOOST_LOG_TRIVIAL(info) << "finished ANIMATION state";
}

void flurlicht::handleERRORState()
{
    BOOST_LOG_TRIVIAL(info) << "finished ERROR state";
}

auto flurlicht::getAnimationState() -> bool
{
    return LEDs_->getAnimationRunning();
}
