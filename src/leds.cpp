#include "leds.h"
#include <memory>
#include <vector>
#include <boost/log/trivial.hpp>
#include "animations.h"

LEDs::LEDs(int pin, int count, int type)
{
    BOOST_LOG_TRIVIAL(debug) << "calling LEDs constructor";
    setAnimationState(false);
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

void LEDs::playAnimation(ANIMATION::fades_t direction)
{
    BOOST_LOG_TRIVIAL(debug) << "playAnimation";
    //BOOST_LOG_TRIVIAL(debug) << "brightness " <<ledstring_->channel[0].brightness;
    //BOOST_LOG_TRIVIAL(debug) << "count " <<ledstring_->channel[0].count;
    //BOOST_LOG_TRIVIAL(debug) << "led0 " <<&ledstring_->channel[0].leds[0];
    //ledstring_->channel[0].leds[0]=0;
    //BOOST_LOG_TRIVIAL(debug) << "led0 " <<&ledstring_->channel[0].leds[0];
    //ANIMATION Animation(ledstring_);
    std::vector<ANIMATION*> pAnimation;
//    std::shared_ptr<ANIMATION> pAnimation;
    if (direction == ANIMATION::fades_t::FADE_IN)
    {
        BOOST_LOG_TRIVIAL(debug) << "creating ANIMATION_ALLFADE";
//        std::shared_ptr<ANIMATION_ALLFADE> pAnimation = std::make_shared<ANIMATION_ALLFADE>(ledstring_);
        pAnimation.push_back(new ANIMATION_ALLFADE(ledstring_));
    }
    else
    {
        BOOST_LOG_TRIVIAL(debug) << "creating ANIMATION_BLINK";
//        std::shared_ptr<ANIMATION_BLINK> pAnimation = std::make_shared<ANIMATION_BLINK>(ledstring_);
        pAnimation.push_back(new ANIMATION_BLINK(ledstring_));
    }
    BOOST_LOG_TRIVIAL(debug) << "creating ANIMATION finished";
    setAnimationState(true);

    BOOST_LOG_TRIVIAL(debug) << "starting animation";
    while(getAnimationRunning())
    {
        setAnimationState(pAnimation[0]->doIncrement(direction));
    }
    BOOST_LOG_TRIVIAL(debug) << "playAnimation finished";
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

bool LEDs::getAnimationRunning()
{
    return animation_running_;
}

void LEDs::setAnimationState(bool state)
{
    animation_running_ = state;
}
