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
    ANIMATION(std::shared_ptr<ws2811_t> ledstring, int step_size);
    virtual ~ANIMATION();

    typedef enum {FADE_IN,FADE_OUT} fades_t;
    virtual bool doIncrement(fades_t direction)=0;


protected:
    typedef ws2811_led_t led_t;
    const led_t cMax_brightness_ = MAX_BRIGHTNESS;

    led_t step_size_;
    led_t max_steps_;
    led_t current_step_ =0;
    auto getIncrement();
    auto getStepSize();
    auto calcMaxSteps();
    auto getCurrentStep();
    led_t calcNextBrightness();
    //timing
    void resetLastRenderTime();
    //bool checkRenderTimeValid();
    //set leds
    void setAllLEDsOneValue(led_t value);
    void renderLEDs();
    std::chrono::high_resolution_clock::time_point last_render_time_;
    static const auto cDelta_ = 10;

private:
    //leds
    std::shared_ptr<ws2811_t> ledstring_;
    //timing



};
#endif // ANIMATIONS_BASE_H

