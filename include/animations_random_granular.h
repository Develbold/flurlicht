#ifndef ANIMATIONS_RANDOM_GRANULAR_H
#define ANIMATIONS_RANDOM_GRANULAR_H

#include <memory>
#include <chrono>
#include <boost/log/trivial.hpp>
#include "animations_base.h"
#include <vector>
#include <list>


// turn on or off all LEDs in random order
class ANIMATION_RANDOM_GRANULAR: public ANIMATION
{
public:
    ANIMATION_RANDOM_GRANULAR(const std::shared_ptr<ws2811_t>& ledstring);
    ~ANIMATION_RANDOM_GRANULAR();
    void render(fades_t direction) override;
private:
//    int getValidLED(ANIMATION::fades_t direction);
//    std::vector<pwm_steps_t> led_pool_;
//    void initLEDPoolIterators(ANIMATION::fades_t direction);
    void initLEDPool(ANIMATION::fades_t direction);
    bool updateLEDBufferOnceRandomly(ANIMATION::fades_t direction);
    pwm_steps_t getLEDStep(unsigned long id);
    void setLEDStep(unsigned long id, pwm_steps_t step);
    bool checkValidLEDToChangeStep(unsigned long id);
    //create buffer
    typedef std::pair<int,uint8_t> pair_t;
    std::vector<pair_t> led_pool_;
};

#endif // ANIMATIONS_RANDOM_GRANULAR_H

