#include "animations_base.h"
#include "flurlicht_tools.h"
#include <animations_base.h>
#include <utility>


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

void ANIMATION::setRange(unsigned start, unsigned end, led_t value)
{
    for(auto i=start;i<=end;i++)
    {
        ledstring_->channel[0].leds[i] = value;
    }
}

ANIMATION::led_t ANIMATION::getOneLEDBrightness(unsigned pos)
{
    return ledstring_->channel[0].leds[pos];
}

//shift the leds up, without "ringbuffer"
void ANIMATION::shiftLEDsUP()
{
    auto n = ledstring_->channel[0].count;
    //auto temp = ledstring_->channel[0].leds[n];
    for(auto i=n;i!=0;i--)
    {
        ledstring_->channel[0].leds[i] = ledstring_->channel[0].leds[i-1];
    }
    //ledstring_->channel[0].leds[n-1] = temp;
}

int ANIMATION::getLEDCount()
{
    return ledstring_->channel[0].count;
}

ANIMATION::pwm_steps_t ANIMATION::getPWMValue(int pos)
{
    if(pos >= pwm_table_size)
    {
        return pwmtable_.at(pwm_table_size-1);
    }
    else
    {
     return pwmtable_.at(pos);
    }
}

void ANIMATION::renderLEDs()
{
    ws2811_render(ledstring_.get());
    ws2811_wait(ledstring_.get());
}

ANIMATION::ANIMATION(std::shared_ptr<ws2811_t> ledstring)
{
    BOOST_LOG_TRIVIAL(debug) << "ANIMATION: base constructor called";
    ledstring_ = std::move(ledstring);
    last_render_time_ = FLURLICHT_TOOLS::getTime();
    seed_ = std::chrono::system_clock::now().time_since_epoch().count();
    pwmtable_={0, 1, 2, 2, 2, 3, 3, 4, 5, 6, 7, 8, 10, 11, 13, 16, 19, 23, 27, 32, 38, 45, 54, 64, 76, 91, 108, 128, 152, 181, 215, 255};
}

ANIMATION::ANIMATION(std::shared_ptr<ws2811_t> ledstring, int time_delta): ANIMATION(ledstring)
{
    this->cDelta_=time_delta;
}

ANIMATION::~ANIMATION()
{

}
