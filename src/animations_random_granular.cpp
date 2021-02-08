#include "animations_random_granular.h"
#include "flurlicht_tools.h"
#include <utility>


ANIMATION_RANDOM_GRANULAR::ANIMATION_RANDOM_GRANULAR(const std::shared_ptr<ws2811_t>& ledstring): ANIMATION(ledstring)
{
    BOOST_LOG_TRIVIAL(debug) << "ANIMATION_RANDOM_GRANULAR: constructor called";
    setTimeDelta(5);
    initLEDPoolIterators(FADE_IN);
    pwmtable_={0, 1, 2, 2, 2, 3, 3, 4, 5, 6, 7, 8, 10, 11, 13, 16, 19, 23, 27, 32, 38, 45, 54, 64, 76, 91, 108, 128, 152, 181, 215, 255};
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

//TODO use iterators instead of array access
void ANIMATION_RANDOM_GRANULAR::render(ANIMATION::fades_t direction)
{
    while(!led_pool_.empty())
    {
        updateLEDBufferOnceRandomly(direction);
        // render and update
        renderLEDs();
    //        resetLastRenderTime();
    }
    BOOST_LOG_TRIVIAL(debug) << "no more LEDs available, animation finished";
    resetLastRenderTime();
}

void ANIMATION_RANDOM_GRANULAR::initLEDPoolIterators(ANIMATION::fades_t direction)
{
    for(auto led=0;led<getLEDCount();led++)
    {
        if (direction==FADE_IN)
        {
            led_pool_.push_back(0);
        }
        else
        {
            led_pool_.push_back(pwmtable_.size()-1);
        }
    }
}
