#ifndef LEDS_H
#define LEDS_H

#include <memory>
#include "animations_base.h"

extern "C" {
#include "rpi_ws281x_static/ws2811.h"
}

// defaults for cmdline options
#define TARGET_FREQ             WS2811_TARGET_FREQ
//#define GPIO_PIN                18
#define DMA                     10
//#define STRIP_TYPE            WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE              WS2811_STRIP_GBR		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)

//#define LED_COUNT               (4 * 60)

class LEDs
{
public:
    LEDs(int pin, int count, int type);
    typedef enum
    {
        BLINK,
        ALL,
        RANDOM,
        RANDOM_GRANULAR,
        SCANNER
    } animations_t;

    void playAnimation(animations_t type, ANIMATION::fades_t direction);
    bool returnWorkingState();
    bool getAnimationRunning();
    animations_t getRandomAnimation();

private:
    std::shared_ptr<ws2811_t> ledstring_;
    ws2811_return_t return_state_;
    bool animation_running_=false;
    void setAnimationState(bool state);
    //ws2811_t ledstring_;
};

#endif // LEDS_H
