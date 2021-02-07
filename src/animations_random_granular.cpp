#include "animations_random_granular.h"
#include "flurlicht_tools.h"
#include <utility>


ANIMATION_RANDOM_GRANULAR::ANIMATION_RANDOM_GRANULAR(const std::shared_ptr<ws2811_t>& ledstring): ANIMATION(ledstring)
{
    BOOST_LOG_TRIVIAL(debug) << "ANIMATION_RANDOM_GRANULAR: constructor called";
    setTimeDelta(5);
    initLEDPool();
//    for(auto led=0;led<ledstring->channel[0].count;led++)
//    {
//        led_pool_.push_back(led);
//    }
//    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

//    shuffle (led_pool_.begin(), led_pool_.end(), std::default_random_engine(seed));

}

ANIMATION_RANDOM_GRANULAR::~ANIMATION_RANDOM_GRANULAR()
{
    //~ANIMATION();
}

auto ANIMATION_RANDOM_GRANULAR::doIncrement(ANIMATION::fades_t direction) -> bool
{
    if (FLURLICHT_TOOLS::checkRenderTimeValid(last_render_time_,getTimeDelta()))
    {
        int led = getValidLED(direction);
        // if no error was returned, proceed
        if (led > -1)
        {
            auto brightness = getOneLEDBrightness(led);
            // set value
            if (direction==FADE_IN)
            {
                brightness += cstep_size_;
                if (brightness > cMax_brightness_)
                {
                    brightness = cMax_brightness_;
                }
                setOneLED(led,brightness);
            }
            else
            {
                brightness -= cstep_size_;
                if (brightness < 0)
                {
                    brightness = 0;
                }
                setOneLED(led,brightness);
            }
            renderLEDs();
            resetLastRenderTime();
        }
        else
        {
            BOOST_LOG_TRIVIAL(debug) << "no more LEDs available, animation finished";
            return false;
        }


    }
    return true;
}

int ANIMATION_RANDOM_GRANULAR::getValidLED(ANIMATION::fades_t direction)
{
    while(!led_pool_.empty())
    {
        shuffleLEDPool();
        // get random led
        auto led = led_pool_.back();
        // get brightness
        auto brightness = getOneLEDBrightness(led);
        //check if max or min brightness is reached
        if (direction==FADE_IN)
        {
            // if max brightness already reached, delete led
            // otherwise return led
            if(brightness==cMax_brightness_)
            {
                led_pool_.pop_back();
            }
            else
            {
                return led;
            }
        }
        else
        {
            // if max brightness already reached, delete led
            // otherwise return led
            if(brightness==0)
            {
                led_pool_.pop_back();
            }
            else
            {
                return led;
            }
        }
    }
    // return negative led as error
    return -1;
}
