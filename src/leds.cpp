#include "leds.h"
#include <memory>
#include <vector>
#include <boost/log/trivial.hpp>

LEDs::LEDs(int pin, int count, int type)
{
    BOOST_LOG_TRIVIAL(debug) << "calling LEDs constructor";
    //init ledstring
    ws2811_channel_t ChannelBuffer = {
                        .gpionum = pin,
                        .invert = 0,
                        .count = count,
                        .strip_type = type,
                        .brightness = 255,
    };
    ledstring_ = std::make_shared<ws2811_t>();
    ledstring_->freq = TARGET_FREQ;
    ledstring_->dmanum = DMA;
    ledstring_->channel[0]=ChannelBuffer;    
    return_state_ = ws2811_init(ledstring_.get());
    BOOST_LOG_TRIVIAL(debug) << "ws2811 return value:" << return_state_;
    BOOST_LOG_TRIVIAL(debug) << "finished LEDs constructor";
}

bool LEDs::playAnimation()
{
    BOOST_LOG_TRIVIAL(debug) << "playAnimation";
    //BOOST_LOG_TRIVIAL(debug) << "brightness " <<ledstring_->channel[0].brightness;
    //BOOST_LOG_TRIVIAL(debug) << "count " <<ledstring_->channel[0].count;
    //BOOST_LOG_TRIVIAL(debug) << "led0 " <<&ledstring_->channel[0].leds[0];
    //ledstring_->channel[0].leds[0]=0;
    //BOOST_LOG_TRIVIAL(debug) << "led0 " <<&ledstring_->channel[0].leds[0];
    ANIMATION Animation(ledstring_);
    bool state = true;



    while(state)
    {
        state = Animation.doIncrement();
    }
    BOOST_LOG_TRIVIAL(debug) << "playAnimation finished";
    return true;
}

bool LEDs::returnWorkingState()
{
    if (return_state_ == WS2811_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

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
        for(ws2811_led_t led=0;led<ledstring_->channel[0].count;led++)
        {
            ledstring_->channel[0].leds[led]+=getStepSize();
        }
        //BOOST_LOG_TRIVIAL(debug) << "render";
        ws2811_render(ledstring_.get());
        last_render_time_ = getTime();
        ws2811_wait(ledstring_.get());
        //if max value is reached, signal finish
        current_step_++;
        if (current_step_ == max_steps_)
        {
            BOOST_LOG_TRIVIAL(debug) << "reached max increment, animation finished";
            return false;
        }
    }
    return true;
}
