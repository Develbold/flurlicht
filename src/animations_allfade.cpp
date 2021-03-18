#include "animations_allfade.h"
#include "flurlicht_tools.h"
#include <random>
#include <utility>

ANIMATION_ALLFADE::ANIMATION_ALLFADE(std::shared_ptr<ws2811_t> ledstring, fades_t direction): ANIMATION(std::move(ledstring))
{
    BOOST_LOG_TRIVIAL(debug) << "ANIMATION_ALLFADE: constructor called";
    direction_ = direction;
    // init vector holding the precalculated brighntesses
    auto step_size = cMax_brightness_/cMax_steps_;
    for(auto i=0;i<cMax_steps_;i++)
    {
        auto step = i*step_size;
        brightness_list_.push_back(step);
    }
    // init the iterator, depending on brightness
    if (direction==FADE_IN)
    {
        brightness_it_ = brightness_list_.begin();
    }
    else
    {
        brightness_it_ = brightness_list_.end();
    }
}

ANIMATION_ALLFADE::~ANIMATION_ALLFADE()
{
    //~ANIMATION();
}

// return the next brightness depending on the direction
ANIMATION::led_t ANIMATION_ALLFADE::calcNextBrightness()
{
    ANIMATION::led_t buffer = 0;

    if (direction_==FADE_IN)
    {
        buffer= *brightness_it_;
        ++brightness_it_;
    }
    else
    {
        buffer= *brightness_it_;
        --brightness_it_;
    }
    return buffer;
}

// check if animation is finished, depending on direction
bool ANIMATION_ALLFADE::checkAnimationFinished()
{
    if (direction_==FADE_IN)
    {
        return brightness_it_==brightness_list_.end();
    }
    else
    {
        return brightness_it_==brightness_list_.begin();
    }
}

void ANIMATION_ALLFADE::render(fades_t direction)
{
    while(true)
    {
        if (FLURLICHT_TOOLS::checkRenderTimeValid(last_render_time_,getTimeDelta()))
        {
            setAllLEDsOneValue(calcNextBrightness());
            renderLEDs();
            resetLastRenderTime();
            //if max value is reached, signal finish
            if (checkAnimationFinished())
            {
                BOOST_LOG_TRIVIAL(debug) << "reached end/begin increment, animation finished";
                break;
            }
        }
    }
}

