#ifndef ANIMATIONS_BLINK_H
#define ANIMATIONS_BLINK_H

#include <memory>
#include <chrono>
#include <boost/log/trivial.hpp>
#include "animations_base.h"
#include <vector>
#include <list>


// turn on or off all LEDs at the same time
class ANIMATION_BLINK: public ANIMATION
{
public:
    ANIMATION_BLINK(std::shared_ptr<ws2811_t> ledstring);
    ~ANIMATION_BLINK();
    void render(fades_t direction) override;
};

#endif // ANIMATIONS_BLINK_H

