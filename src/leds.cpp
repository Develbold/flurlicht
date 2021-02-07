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

//TODO use shared pointer
void LEDs::playAnimation(animations_t type, ANIMATION::fades_t direction)
{
    BOOST_LOG_TRIVIAL(debug) << "playAnimation";

    std::vector<ANIMATION*> pAnimation;

    switch (type)
    {
        case BLINK:
            BOOST_LOG_TRIVIAL(debug) << "creating ANIMATION_BLINK";
            pAnimation.push_back(new ANIMATION_BLINK(ledstring_));
        break;
        case ALL:
            BOOST_LOG_TRIVIAL(debug) << "creating ANIMATION_ALLFADE";
            pAnimation.push_back(new ANIMATION_ALLFADE(ledstring_, direction));
        break;
        case RANDOM:
            BOOST_LOG_TRIVIAL(debug) << "creating ANIMATION_ALLFADE";
            pAnimation.push_back(new ANIMATION_RANDOM(ledstring_));
        break;
        default:
            BOOST_LOG_TRIVIAL(error) << "unknown animations";
        break;
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

auto LEDs::returnWorkingState() -> bool
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

auto LEDs::getAnimationRunning() -> bool
{
    return animation_running_;
}

// return random animation type
LEDs::animations_t LEDs::getRandomAnimation()
{
    std::vector<LEDs::animations_t> buffer{LEDs::ALL,LEDs::RANDOM};
    return buffer[rand() % buffer.size()];
}

void LEDs::setAnimationState(bool state)
{
    animation_running_ = state;
}
