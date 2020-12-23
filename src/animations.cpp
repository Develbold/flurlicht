#include "animations.h"
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
    // init the iterator, dependin gon brightness
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

auto ANIMATION_ALLFADE::doIncrement(fades_t direction) -> bool
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
            return false;
        }
    }
    return true;
}

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

ANIMATION_RANDOM::ANIMATION_RANDOM(const std::shared_ptr<ws2811_t>& ledstring): ANIMATION(ledstring)
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
