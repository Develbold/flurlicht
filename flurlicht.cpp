#include "flurlicht.h"
#include <iostream>
#include <chrono>
#include <thread>

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
    setNextState(ST_OFF);
    //
    initGPIO();
}



void flurlicht::run()
{
    cout << "INFO: entered loop" << endl;
    while(true)
    {
        States NextState = getNextState();
        setNextState(NextState);
        switch (NextState)
        {
            case ST_OFF:
                cout << "INFO: switched to OFF state" << endl;
                sleepPeriod(1000);
            break;
            case ST_ON:
                cout << "INFO: switched to ON state" << endl;
                sleepPeriod(1000);
            break;
            case ST_ANIMATION:
                cout << "INFO: switched to Animation state" << endl;
                sleepPeriod(1000);
            break;
            case ST_ERROR:
                cout << "ERROR: switched to ERROR STATE!" << endl;
                sleepPeriod(1000);
            break;
            default:
                cout << "ERROR: switched to Undefined STATE!" << endl;
                sleepPeriod(1000);
        }
    }
    cout << "INFO: finished loop" << endl;
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

void flurlicht::sleepPeriod(int period)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(period));
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
