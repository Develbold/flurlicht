#ifndef FLURLICHT_H
#define FLURLICHT_H

#include <iostream>
extern "C" {
#include "extern/pigpio/pigpio.h"
#include "extern/rpi_ws281x/ws2811.h"
}

// defaults for cmdline options
#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN                18
#define DMA                     10
//#define STRIP_TYPE            WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds
#define STRIP_TYPE              WS2811_STRIP_GBR		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)

#define LED_COUNT               (4 * 60)

class flurlicht
{
public:
    flurlicht();
    void run();

private:
    void readSensors();
    enum States
    {
        ST_OFF,
        ST_ANIMATION,
        ST_ON,
        ST_ERROR
    };
    States getNextState();
    void setNextState(States next);
    States getCurrentState();
    States CurrentState_;
    //Sensor handling
    struct SensorStates
    {
        bool front;
        bool back;
    };
    SensorStates Sensors_;
    SensorStates getSensorStates();
    void setSensorStateFront(bool state);
    void setSensorStateBack(bool state);
    bool getAnimationState();
    void setAnimationState(bool state);
    bool AnimationState_;

    //GPIO stuff
    bool initGPIO();
    void handleGPIOCallback(int gpio, int level, uint32_t tick);
    static void handleGPIOCallbackExt(int gpio, int level, uint32_t tick,void *user);
    const int PinFront_ = 14;
    const int PinBack_ = 15;
};

#endif // FLURLICHT_H
