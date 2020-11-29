#include "animations_base.h"

std::chrono::high_resolution_clock::time_point ANIMATION::getTime()
{
    return std::chrono::high_resolution_clock::now();
}

bool ANIMATION::checkRenderTimeValid()
{
    //check if it is time to render
    auto time_delta = std::chrono::duration_cast<std::chrono::milliseconds>(getTime() - last_render_time_);

    return time_delta.count()>cDelta_;
}

auto ANIMATION::getStepSize()
{
    return step_size_;
}

auto ANIMATION::calcMaxSteps()
{
    return cMax_brightness_/getStepSize();
}

auto ANIMATION::getCurrentStep()
{
    return current_step_;
}

ANIMATION::led_t ANIMATION::calcNextBrightness()
{
    return getStepSize()*getCurrentStep();
}

void ANIMATION::resetLastRenderTime()
{
    last_render_time_ = getTime();
}

void ANIMATION::setAllLEDsOneValue(led_t value)
{
    for(led_t led=0;led<ledstring_->channel[0].count;led++)
    {
        ledstring_->channel[0].leds[led] = value;
    }
}

void ANIMATION::renderLEDs()
{
    ws2811_render(ledstring_.get());
    ws2811_wait(ledstring_.get());
}

ANIMATION::ANIMATION(std::shared_ptr<ws2811_t> ledstring)
{
    ledstring_ = ledstring;
    last_render_time_ = getTime();
    step_size_ = getStepSize();
    max_steps_ = calcMaxSteps();
    //BOOST_LOG_TRIVIAL(debug) << "maximum number of steps: " << max_steps_;
}

ANIMATION::~ANIMATION()
{

}
