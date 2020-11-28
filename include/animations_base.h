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

    typedef enum {FADE_IN,FADE_OUT} fades_t;
    virtual bool doIncrement(fades_t direction)=0;


protected:
    typedef ws2811_led_t led_t;

    led_t step_size_ = 1;
    led_t max_steps_;
    led_t current_step_ =0;
    auto getIncrement();
    auto getStepSize();
    auto calcMaxSteps();
    auto getCurrentStep();
    led_t calcNextBrightness();
    //timing
    void resetLastRenderTime();
    bool checkRenderTimeValid();
    //set leds
    void setAllLEDsOneValue(led_t value);
    void renderLEDs();

private:
    //leds
    const led_t cMax_brightness_ = MAX_BRIGHTNESS;
    std::shared_ptr<ws2811_t> ledstring_;
    //timing
    static const auto cDelta_ = 10;
    std::chrono::high_resolution_clock::time_point getTime();
    std::chrono::high_resolution_clock::time_point last_render_time_;

};
#endif // ANIMATIONS_BASE_H

