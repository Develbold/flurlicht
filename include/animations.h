#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <memory>
#include <chrono>
#include <boost/log/trivial.hpp>
#include "animations_base.h"
#include <vector>
#include <list>

class ANIMATION_ALLFADE: public ANIMATION
{
public:
    ANIMATION_ALLFADE(std::shared_ptr<ws2811_t> ledstring, fades_t direction);
    ~ANIMATION_ALLFADE();
    bool doIncrement(fades_t direction) override;

private:
    const unsigned cMax_steps_ = 15;

    std::list<ANIMATION::led_t>brightness_list_;
    std::list<ANIMATION::led_t>::iterator brightness_it_;

    ANIMATION::led_t calcNextBrightness();
    bool checkAnimationFinished();
};

class ANIMATION_BLINK: public ANIMATION
{
public:
    ANIMATION_BLINK(std::shared_ptr<ws2811_t> ledstring);
    ~ANIMATION_BLINK();
    bool doIncrement(fades_t direction) override;
};

class ANIMATION_RANDOM: public ANIMATION
{
public:
    ANIMATION_RANDOM(const std::shared_ptr<ws2811_t>& ledstring);
    ~ANIMATION_RANDOM();
    bool doIncrement(fades_t direction) override;
};

#endif // ANIMATIONS_H

