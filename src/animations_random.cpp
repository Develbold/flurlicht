#include "animations_random.h"
#include "flurlicht_tools.h"
#include <utility>
#include <random>


ANIMATION_RANDOM::ANIMATION_RANDOM(const std::shared_ptr<ws2811_t>& ledstring): ANIMATION(ledstring)
{
    BOOST_LOG_TRIVIAL(debug) << "ANIMATION_RANDOM: constructor called";
    setTimeDelta(5);
    initLEDPoolByCount();
    shuffleLEDPool();
}

ANIMATION_RANDOM::~ANIMATION_RANDOM()
{
    //~ANIMATION();
}

auto ANIMATION_RANDOM::doIncrement(ANIMATION::fades_t direction) -> bool
{
    if (FLURLICHT_TOOLS::checkRenderTimeValid(last_render_time_,getTimeDelta()))
    {
        if(!led_pool_.empty())
        {
            // get random led
            auto led = led_pool_.back();
            led_pool_.pop_back();
            // set value
            //BOOST_LOG_TRIVIAL(debug) << "one: " << led <<"|"<<cMax_brightness_<<"|"<<led_pool_.size();
            if (direction==FADE_IN)
            {
                setOneLED(led,cMax_brightness_);
            }
            else
            {
                setOneLED(led,0);
            }
            renderLEDs();
            resetLastRenderTime();
        }
        else
        {
            BOOST_LOG_TRIVIAL(debug) << "reached max increment, animation finished";
            return false;
        }

    }
    return true;
}

void ANIMATION_RANDOM::initLEDPoolByCount()
{
    for(auto led=0;led<getLEDCount();led++)
    {
        led_pool_.push_back(led);
    }
}

void ANIMATION_RANDOM::shuffleLEDPool()
{
    shuffle (led_pool_.begin(), led_pool_.end(), std::default_random_engine(seed_));
}
