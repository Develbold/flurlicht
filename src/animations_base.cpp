#include "animations_base.h"

auto ANIMATION::getTime()
{
    return std::chrono::high_resolution_clock::now();
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

ws2811_led_t ANIMATION::calcNextBrightness()
{
    return getStepSize()*getCurrentStep();
}

ANIMATION::ANIMATION(std::shared_ptr<ws2811_t> ledstring)
{
    ledstring_ = ledstring;
    last_render_time_ = getTime();
    step_size_ = getStepSize();
    max_steps_ = calcMaxSteps();
    BOOST_LOG_TRIVIAL(debug) << "maximum number of steps: " << max_steps_;
}

bool ANIMATION::doIncrement()
{
    //check if it is time to render
    auto time_delta = std::chrono::duration_cast<std::chrono::milliseconds>(getTime() - last_render_time_);

    if (time_delta.count()>cDelta)
    {
        auto next_brightness = calcNextBrightness();
        for(ws2811_led_t led=0;led<ledstring_->channel[0].count;led++)
        {
            ledstring_->channel[0].leds[led] = next_brightness;
        }
        //BOOST_LOG_TRIVIAL(debug) << "render";
        ws2811_render(ledstring_.get());
        last_render_time_ = getTime();
        ws2811_wait(ledstring_.get());
        //if max value is reached, signal finish
        current_step_++;
        //BOOST_LOG_TRIVIAL(debug) << "current step:" << current_step_;
        if (current_step_ >= max_steps_)
        {
            BOOST_LOG_TRIVIAL(debug) << "reached max increment, animation finished";
            return false;
        }
    }
    return true;
}
