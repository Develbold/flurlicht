#include "animations.h"

ANIMATION_ALLFADE::ANIMATION_ALLFADE(std::shared_ptr<ws2811_t> ledstring): ANIMATION(ledstring)
{
    BOOST_LOG_TRIVIAL(debug) << "ANIMATION_ALLFADE: constructor called";
}

ANIMATION_ALLFADE::~ANIMATION_ALLFADE()
{
    //~ANIMATION();
}

bool ANIMATION_ALLFADE::doIncrement(fades_t direction)
{
    if (checkRenderTimeValid())
    {
        setAllLEDsOneValue(calcNextBrightness());
        renderLEDs();
        resetLastRenderTime();
        //if max value is reached, signal finish
        current_step_++;
        if (current_step_ >= max_steps_)
        {
            BOOST_LOG_TRIVIAL(debug) << "reached max increment, animation finished";
            return false;
        }
    }
    return true;
}

ANIMATION_BLINK::ANIMATION_BLINK(std::shared_ptr<ws2811_t> ledstring): ANIMATION(ledstring)
{
    BOOST_LOG_TRIVIAL(debug) << "ANIMATION_BLINK: constructor called";
}

ANIMATION_BLINK::~ANIMATION_BLINK()
{
    //~ANIMATION();
}

bool ANIMATION_BLINK::doIncrement(fades_t direction)
{
    if (checkRenderTimeValid())
    {
        setAllLEDsOneValue(0);
        renderLEDs();
        resetLastRenderTime();
        //if max value is reached, signal finish
        current_step_++;
        if (current_step_ >= max_steps_)
        {
            BOOST_LOG_TRIVIAL(debug) << "reached max increment, animation finished";
            return false;
        }
    }
    return true;
}
