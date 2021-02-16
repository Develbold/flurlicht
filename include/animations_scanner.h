#ifndef ANIMATION_SCANNER_H
#define ANIMATION_SCANNER_H

#include <memory>
#include <chrono>
#include <boost/log/trivial.hpp>
#include "animations_base.h"
#include <vector>
#include <list>


// turn on or off all LEDs at the same time
class ANIMATION_SCANNER: public ANIMATION
{
public:
    ANIMATION_SCANNER(std::shared_ptr<ws2811_t> ledstring);
    ~ANIMATION_SCANNER();
    void render(fades_t direction) override;
};

#endif // ANIMATION_SCANNER_H

