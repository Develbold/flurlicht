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

void LEDs::playAnimation()
{
    BOOST_LOG_TRIVIAL(debug) << "playAnimation";
    BOOST_LOG_TRIVIAL(debug) << "brightness " <<ledstring_->channel[0].brightness;
    BOOST_LOG_TRIVIAL(debug) << "count " <<ledstring_->channel[0].count;
    BOOST_LOG_TRIVIAL(debug) << "led0 " <<&ledstring_->channel[0].leds[0];
    //ledstring_->channel[0].leds[0]=0;
    BOOST_LOG_TRIVIAL(debug) << "led0 " <<&ledstring_->channel[0].leds[0];

//    while(animating)
//    {
        for(uint8_t bright=0;bright<ledstring_->channel[0].brightness;bright++)
        {
            for(ws2811_led_t led=0;led<ledstring_->channel[0].count;led++)
            {
                ledstring_->channel[0].leds[led]=bright;
            }
            BOOST_LOG_TRIVIAL(debug) << "render";
            ws2811_render(ledstring_.get());
            ws2811_wait(ledstring_.get());
        }
        //    }
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
