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
    virtual void render(fades_t direction)=0;

protected:
    typedef ws2811_led_t led_t;
    const led_t cMax_brightness_ = MAX_BRIGHTNESS;

//    led_t current_step_ =0;
//    std::vector<unsigned int> led_pool_;
    unsigned seed_;
//    void initLEDPool();
//    void initLEDPoolByCount();
//    void initLEDPoolByValue(unsigned int value);
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
    led_t getOneLEDBrightness(unsigned pos);
    int getLEDCount();

    ANIMATION::fades_t direction_;

//    static const std::vector<uint16_t> pwmtable_;
//    static std::vector<uint16_t> pwmtable_;
//    static const unsigned c_pwmtable_size_=32;
//    typedef std::array<uint16_t,c_pwmtable_size_> pwmtable_t;
//    typedef pwmtable_t::iterator pwmtable_it;
//    static constexpr pwmtable_t c_pwmtable_={0, 1, 2, 2, 2, 3, 3, 4, 5, 6, 7, 8, 10, 11, 13, 16, 19, 23, 27, 32, 38, 45, 54, 64, 76, 91, 108, 128, 152, 181, 215, 255};
    std::array<uint16_t,32> pwmtable_;

private:
    //leds
    std::shared_ptr<ws2811_t> ledstring_;
    //timing

    int cDelta_{};
};

//const std::vector<uint16_t> ANIMATION::pwmtable_({0, 1, 2, 2, 2, 3, 3, 4, 5, 6, 7, 8, 10, 11, 13, 16, 19, 23, 27, 32, 38, 45, 54, 64, 76, 91, 108, 128, 152, 181, 215, 255});
#endif // ANIMATIONS_BASE_H

