#ifndef ANIMATIONS_RANDOM_H
#define ANIMATIONS_RANDOM_H

#include <memory>
#include <chrono>
#include <boost/log/trivial.hpp>
#include "animations_base.h"
#include <vector>
#include <list>


// turn on or off all LEDs in random order
class ANIMATION_RANDOM: public ANIMATION
{
public:
    ANIMATION_RANDOM(const std::shared_ptr<ws2811_t>& ledstring);
    ~ANIMATION_RANDOM();
    bool doIncrement(fades_t direction) override;
private:
    std::vector<unsigned int> led_pool_;
    void shuffleLEDPool();
    void initLEDPoolByCount();
};

#endif // ANIMATIONS_RANDOM_H

