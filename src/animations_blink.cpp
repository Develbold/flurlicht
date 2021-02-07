#include "animations_blink.h"
#include "flurlicht_tools.h"
#include <random>
#include <utility>


ANIMATION_BLINK::ANIMATION_BLINK(std::shared_ptr<ws2811_t> ledstring): ANIMATION(std::move(ledstring))
{
    BOOST_LOG_TRIVIAL(debug) << "ANIMATION_BLINK: constructor called";
}

ANIMATION_BLINK::~ANIMATION_BLINK()
{
    //~ANIMATION();
}

auto ANIMATION_BLINK::doIncrement(fades_t direction) -> bool
{
    if (direction == FADE_OUT)
    {
        setAllLEDsOneValue(0);
    }
    else
    {
        setAllLEDsOneValue(cMax_brightness_);
    }
    renderLEDs();
    resetLastRenderTime();
    return false;
}

