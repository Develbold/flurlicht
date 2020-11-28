#include "animations.h"

ANIMATION_ALLFADE::ANIMATION_ALLFADE(std::shared_ptr<ws2811_t> ledstring): ANIMATION(ledstring)
{

}

ANIMATION_ALLFADE::~ANIMATION_ALLFADE()
{
    //~ANIMATION();
}

bool ANIMATION_ALLFADE::doIncrement()
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

bool ANIMATION_ALLFADE::doDecrement()
{

}
