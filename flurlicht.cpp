#include "flurlicht.h"
#include <iostream>


using namespace std;

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
    Sensors_.back = false;
    Sensors_.front = false;
    setNextState(ST_ON);
    //
    initGPIO();
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
    CurrentState_ = next;
}

flurlicht::States flurlicht::getCurrentState()
{
    return CurrentState_;
}

flurlicht::SensorStates flurlicht::getSensorStates()
{
    SensorStates buffer;
    //buffer.front =this->Sensors.front;
    //buffer.back = this->Sensors.back;
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
    cout << "movement detected! pin:" << gpio << " level: " << level << endl;
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

bool flurlicht::initGPIO()
{
    gpioInitialise();
    //set mode of GPIO
    gpioSetMode(PinFront_, PI_INPUT);
    gpioSetMode(PinBack_, PI_INPUT);
    //register Callbacks
    gpioSetAlertFuncEx(PinFront_, handleGPIOCallbackExt, (void *)this);
    gpioSetAlertFuncEx(PinBack_, handleGPIOCallbackExt, (void *)this);
    cout << "INFO: GPIO intitilaized"<< endl;
    return true;
}


bool flurlicht::getAnimationState()
{
    return this->AnimationState_;
}
