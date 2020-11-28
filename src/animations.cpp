#include "animations.h"

ANIMATION_ALLFADE::ANIMATION_ALLFADE(std::shared_ptr<ws2811_t> ledstring): ANIMATION(ledstring)
{

}

ANIMATION_ALLFADE::~ANIMATION_ALLFADE()
{
    //~ANIMATION();
}

bool ANIMATION_ALLFADE::doIncrement()
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

bool ANIMATION_ALLFADE::doDecrement()
{
    return false;
}
