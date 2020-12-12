#include "animations.h"
#include "flurlicht_tools.h"

ANIMATION_ALLFADE::ANIMATION_ALLFADE(std::shared_ptr<ws2811_t> ledstring): ANIMATION(ledstring,1)
{
    BOOST_LOG_TRIVIAL(debug) << "ANIMATION_ALLFADE: constructor called";
}

ANIMATION_ALLFADE::~ANIMATION_ALLFADE()
{
    //~ANIMATION();
}

bool ANIMATION_ALLFADE::doIncrement(fades_t direction)
{
    if (FLURLICHT_TOOLS::checkRenderTimeValid(last_render_time_,cDelta_))
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

ANIMATION_BLINK::ANIMATION_BLINK(std::shared_ptr<ws2811_t> ledstring): ANIMATION(ledstring,255)
{
    BOOST_LOG_TRIVIAL(debug) << "ANIMATION_BLINK: constructor called";
}

ANIMATION_BLINK::~ANIMATION_BLINK()
{
    //~ANIMATION();
}

bool ANIMATION_BLINK::doIncrement(fades_t direction)
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
