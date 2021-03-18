#ifndef ANIMATIONS_ALLFADE_H
#define ANIMATIONS_ALLFADE_H

#include <memory>
#include <chrono>
#include <boost/log/trivial.hpp>
#include "animations_base.h"
#include <vector>
#include <list>

// fade each LED with the same brightness in sync (as ramp)
class ANIMATION_ALLFADE: public ANIMATION
{
public:
    ANIMATION_ALLFADE(std::shared_ptr<ws2811_t> ledstring, fades_t direction);
    ~ANIMATION_ALLFADE();
    void render(fades_t direction) override;

private:
    const unsigned cMax_steps_ = 15;

    std::list<ANIMATION::led_t>brightness_list_;
    std::list<ANIMATION::led_t>::iterator brightness_it_;

    ANIMATION::led_t calcNextBrightness();
    bool checkAnimationFinished();
};

#endif // ANIMATIONS_ALLFADE_H

