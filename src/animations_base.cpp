#include "animations_base.h"
#include "flurlicht_tools.h"
#include <random>
#include <animations_base.h>

#include <utility>


void ANIMATION::setTimeDelta(int value)
{
    cDelta_ = value;
}

auto ANIMATION::getTimeDelta() -> int
{
    return cDelta_;
}

void ANIMATION::resetLastRenderTime()
{
    last_render_time_ = FLURLICHT_TOOLS::getTime();
}

void ANIMATION::setAllLEDsOneValue(led_t value)
{
    for(led_t led=0;led<ledstring_->channel[0].count;led++)
    {
        ledstring_->channel[0].leds[led] = value;
    }
}

void ANIMATION::setOneLED(unsigned pos, led_t value)
{
    ledstring_->channel[0].leds[pos] = value;
}

ANIMATION::led_t ANIMATION::getOneLEDBrightness(unsigned pos)
{
    return ledstring_->channel[0].leds[pos];
}

int ANIMATION::getLEDCount()
{
    return ledstring_->channel[0].count;
}

void ANIMATION::renderLEDs()
{
    ws2811_render(ledstring_.get());
    ws2811_wait(ledstring_.get());
}

ANIMATION::ANIMATION(std::shared_ptr<ws2811_t> ledstring)
{
    BOOST_LOG_TRIVIAL(debug) << "ANIMATION: base constructor called";
    setTimeDelta(10);
    ledstring_ = std::move(ledstring);
    last_render_time_ = FLURLICHT_TOOLS::getTime();
    seed_ = std::chrono::system_clock::now().time_since_epoch().count();
}

ANIMATION::~ANIMATION()
{

}

void ANIMATION::initLEDPool()
{
    for(auto led=0;led<getLEDCount();led++)
    {
        led_pool_.push_back(led);
    }
}

void ANIMATION::shuffleLEDPool()
{
    shuffle (led_pool_.begin(), led_pool_.end(), std::default_random_engine(seed_));
}
