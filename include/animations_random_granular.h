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
    bool doIncrement(fades_t direction) override;
private:
    int getValidLED(ANIMATION::fades_t direction);
    const static int cstep_size_{10};
};

#endif // ANIMATIONS_RANDOM_GRANULAR_H

