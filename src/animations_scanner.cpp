#include "animations_scanner.h"
#include "flurlicht_tools.h"
#include <random>
#include <utility>


ANIMATION_SCANNER::ANIMATION_SCANNER(std::shared_ptr<ws2811_t> ledstring): ANIMATION(std::move(ledstring))
{
    BOOST_LOG_TRIVIAL(debug) << "ANIMATION_BLINK: constructor called";
}

ANIMATION_SCANNER::~ANIMATION_SCANNER()
{
    //~ANIMATION();
}

void ANIMATION_SCANNER::render(fades_t direction)
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
}

