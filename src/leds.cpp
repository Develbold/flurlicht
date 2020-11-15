#include "leds.h"
#include <memory>
#include <vector>

LEDs::LEDs()
{
    int led_count = LED_COUNT;

    int clear_on_exit = 0;

    ws2811_channel_t ChannelBuffer = {
                        .gpionum = GPIO_PIN,
                        .invert = 0,
                        .count = LED_COUNT,
                        .strip_type = STRIP_TYPE,
                        .brightness = 255,
    };

    ledstring_->freq = TARGET_FREQ;
    ledstring_->dmanum = DMA;
    ledstring_->channel[0]=ChannelBuffer;

//    ledstring_ =
//    {
//        .freq = TARGET_FREQ,
//        .dmanum = DMA,
//        .channel =
//        {
//            [0] =
//            {
//                .gpionum = GPIO_PIN,
//                .invert = 0,
//                .count = LED_COUNT,
//                .strip_type = STRIP_TYPE,
//                .brightness = 255,
//            },
//        }
//    };
    ws2811_init(ledstring_.get());
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
