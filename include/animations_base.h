#ifndef ANIMATIONS_BASE_H
#define ANIMATIONS_BASE_H

#include <memory>
#include <chrono>
#include <boost/log/trivial.hpp>

extern "C" {
#include "rpi_ws281x/ws2811.h"
}

#define MAX_BRIGHTNESS 255

class ANIMATION
{
public:
    ANIMATION(std::shared_ptr<ws2811_t> ledstring);
    virtual ~ANIMATION();
    virtual bool doIncrement()=0;
    virtual bool doDecrement()=0;

protected:
    typedef ws2811_led_t led_t;

    std::shared_ptr<ws2811_t> ledstring_;
    std::chrono::high_resolution_clock::time_point last_render_time_;
    static const auto cDelta = 10;
    led_t step_size_ = 1;
    led_t max_steps_;
    led_t current_step_ =0;
    //const ws2811_led_t cMax_brightness_ = std::numeric_limits<uint32_t>::max();
    const led_t cMax_brightness_ = MAX_BRIGHTNESS;
    std::chrono::high_resolution_clock::time_point getTime();
    auto getIncrement();
    auto getStepSize();
    auto calcMaxSteps();
    auto getCurrentStep();
    led_t calcNextBrightness();
    //set leds
    void setAllLEDsOneValue(auto value);
};
#endif // ANIMATIONS_BASE_H

