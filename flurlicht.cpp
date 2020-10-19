#include "flurlicht.h"
#include "rpi_ws281x/ws2811.h"
#include <iostream>

flurlicht::flurlicht()
{
    int led_count = LED_COUNT;

    int clear_on_exit = 0;

    ws2811_t ledstring =
    {
        .freq = TARGET_FREQ,
        .dmanum = DMA,
        .channel =
        {
            [0] =
            {
                .gpionum = GPIO_PIN,
                .invert = 0,
                .count = LED_COUNT,
                .strip_type = STRIP_TYPE,
                .brightness = 255,
            },
            [1] =
            {
                .gpionum = 0,
                .invert = 0,
                .count = 0,
                .brightness = 0,
            },
        }


    };
    Sensors.back = false;
    Sensors.front = false;
    setNextState(ST_ON);
}



void flurlicht::run()
{
    States NextState = getNextState();
    setNextState(NextState);
    switch (NextState)
    {
        case ST_OFF:
        break;
        case ST_ON:
        break;
        case ST_ANIMATION:
        break;
        case ST_ERROR:
            std::cout << "ERROR STATE!" << std::endl;
        break;
    }
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
    CurrentState = next;
}

flurlicht::States flurlicht::getCurrentState()
{
    return CurrentState;
}

flurlicht::SensorStates flurlicht::getSensorStates()
{
    SensorStates buffer;
    buffer.front =false;
    buffer.back = false;
    return buffer;

}

void flurlicht::setAnimationState(bool state)
{
    AnimationState = state;
}

bool flurlicht::getAnimationState()
{
    return AnimationState;
}
