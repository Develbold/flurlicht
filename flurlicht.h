#ifndef FLURLICHT_H
#define FLURLICHT_H

#include <iostream>


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
    States CurrentState;
    struct SensorStates
    {
        bool front;
        bool back;
    };
    SensorStates Sensors;
    SensorStates getSensorStates();
    bool getAnimationState();
    void setAnimationState(bool state);
    bool AnimationState;
};

#endif // FLURLICHT_H
