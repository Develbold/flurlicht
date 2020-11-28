#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <memory>
#include <chrono>
#include <boost/log/trivial.hpp>
#include "animations_base.h"

class ANIMATION_ALLFADE: ANIMATION
{
public:
    ANIMATION_ALLFADE(std::shared_ptr<ws2811_t> ledstring);
    ~ANIMATION_ALLFADE();
    bool doIncrement() override;
    bool doDecrement() override;
};

class ANIMATION_BLINK: ANIMATION
{
public:
    ANIMATION_BLINK(std::shared_ptr<ws2811_t> ledstring);
    ~ANIMATION_BLINK();
    bool doIncrement() override;
    bool doDecrement() override;
};
#endif // ANIMATIONS_H

