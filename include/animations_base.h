#ifndef ANIMATIONS_BASE_H
#define ANIMATIONS_BASE_H

#include <memory>
#include <chrono>
#include <vector>
#include <boost/log/trivial.hpp>

extern "C" {
#include "rpi_ws281x_static/ws2811.h"
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
    const led_t cMax_brightness_ = MAX_BRIGHTNESS;

//    led_t current_step_ =0;
    std::vector<unsigned int> led_pool_;
    auto getIncrement();
    void setTimeDelta(int value);
    int getTimeDelta();
    //timing
    void resetLastRenderTime();
    //set leds
    void setAllLEDsOneValue(led_t value);
    void renderLEDs();
    std::chrono::high_resolution_clock::time_point last_render_time_;

    void setOneLED(unsigned pos, led_t value);

    ANIMATION::fades_t direction_;

private:
    //leds
    std::shared_ptr<ws2811_t> ledstring_;
    //timing

    int cDelta_;

};
#endif // ANIMATIONS_BASE_H

