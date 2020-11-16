#include "leds.h"
#include <memory>
#include <vector>
#include <boost/log/trivial.hpp>

LEDs::LEDs()
{
    BOOST_LOG_TRIVIAL(debug) << "calling LEDs constructor";
    int led_count = LED_COUNT;

    int clear_on_exit = 0;

    //init ledstring
    ws2811_channel_t ChannelBuffer = {
                        .gpionum = GPIO_PIN,
                        .invert = 0,
                        .count = LED_COUNT,
                        .strip_type = STRIP_TYPE,
                        .brightness = 255,
    };
    ledstring_ = std::make_shared<ws2811_t>();
    ledstring_->freq = TARGET_FREQ;
    ledstring_->dmanum = DMA;
    ledstring_->channel[0]=ChannelBuffer;    
    ws2811_init(ledstring_.get());
    BOOST_LOG_TRIVIAL(debug) << "finished LEDs constructor";
}

void LEDs::playAnimation()
{
    bool animating = true;

//    while(animating)
//    {
        for(auto bright=0;bright<ledstring_->channel[0].brightness;bright++)
        {
            for(auto led=0;led<ledstring_->channel[0].count;led++)
            {
                ledstring_->channel[0].leds[led]=bright;
            }
            ws2811_render(ledstring_.get());
            ws2811_wait(ledstring_.get());
        }
//    }
}
