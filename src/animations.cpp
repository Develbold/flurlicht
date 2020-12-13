#include "animations.h"
#include "flurlicht_tools.h"
#include <random>

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
    if (FLURLICHT_TOOLS::checkRenderTimeValid(last_render_time_,getTimeDelta()))
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

ANIMATION_RANDOM::ANIMATION_RANDOM(std::shared_ptr<ws2811_t> ledstring): ANIMATION(ledstring,1)
{
    BOOST_LOG_TRIVIAL(debug) << "ANIMATION_RANDOM: constructor called";
    setTimeDelta(5);
    for(auto led=0;led<ledstring->channel[0].count;led++)
    {
        led_pool_.push_back(led);
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle (led_pool_.begin(), led_pool_.end(), std::default_random_engine(seed));

}

ANIMATION_RANDOM::~ANIMATION_RANDOM()
{
    //~ANIMATION();
}

bool ANIMATION_RANDOM::doIncrement(ANIMATION::fades_t direction)
{
    if (FLURLICHT_TOOLS::checkRenderTimeValid(last_render_time_,getTimeDelta()))
    {
        // get random led
        auto led = led_pool_.back();
        led_pool_.pop_back();
        // set value
        setOneLED(led,cMax_brightness_);
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
