#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <memory>
#include <chrono>
#include <boost/log/trivial.hpp>
#include "animations_base.h"
#include <vector>

class ANIMATION_ALLFADE: public ANIMATION
{
public:
    ANIMATION_ALLFADE(std::shared_ptr<ws2811_t> ledstring);
    ~ANIMATION_ALLFADE();
    bool doIncrement(fades_t direction) override;
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
private:
    std::vector<unsigned int> led_pool_;
};

#endif // ANIMATIONS_H

