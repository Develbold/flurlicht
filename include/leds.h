#ifndef LEDS_H
#define LEDS_H

#include <memory>
#include <chrono>

extern "C" {
#include "rpi_ws281x/ws2811.h"
}

// defaults for cmdline options
#define TARGET_FREQ             WS2811_TARGET_FREQ
//#define GPIO_PIN                18
#define DMA                     10
//#define STRIP_TYPE            WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE              WS2811_STRIP_GBR		// WS2812/SK6812RGB integrated chip+leds
//#define STRIP_TYPE            SK6812_STRIP_RGBW		// SK6812RGBW (NOT SK6812RGB)

//#define LED_COUNT               (4 * 60)

class ANIMATION
{
public:
    ANIMATION(std::shared_ptr<ws2811_t> ledstring);
    bool doIncrement();
    void doDecrement();

private:
    std::shared_ptr<ws2811_t> ledstring_;
    std::chrono::high_resolution_clock::time_point last_render_time_;
    static const auto cDelta = 10;
    ws2811_led_t step_size_ = 1;
    ws2811_led_t max_steps_;
    ws2811_led_t current_step_ =0;
    const ws2811_led_t cMax_brightness_ = std::numeric_limits<uint32_t>::max();
    auto getTime();
    auto getIncrement();
    auto getStepSize();
    auto calcMaxSteps();
};

class LEDs
{
public:
    LEDs(int pin, int count, int type);
    bool playAnimation();
    bool returnWorkingState();

private:
    std::shared_ptr<ws2811_t> ledstring_;
    ws2811_return_t return_state_;
    //ws2811_t ledstring_;
};

#endif // LEDS_H
