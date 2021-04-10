#include "animations_scanner.h"
#include "flurlicht_tools.h"
#include <random>
#include <utility>


ANIMATION_SCANNER::ANIMATION_SCANNER(std::shared_ptr<ws2811_t> ledstring): ANIMATION(std::move(ledstring))
{
    BOOST_LOG_TRIVIAL(debug) << "ANIMATION_SCANNER: constructor called";
}

ANIMATION_SCANNER::~ANIMATION_SCANNER()
{
    //~ANIMATION();
}

//TODO add direction
void ANIMATION_SCANNER::render(fades_t direction)
{
    auto pos_dot = 0;
    const auto led_count = getLEDCount();
    auto pos_bar_back = led_count;
    auto dot_delta = 5;
    //set initial dot
    setOneLED(0,cMax_brightness_);
    while(0!=pos_bar_back)
    {
        //shift leds
        shiftLEDsUP();
        //add led if dividable by dot_delta
        if(pos_dot%dot_delta==0)
        {
            setOneLED(0,cMax_brightness_);
        }
//        // set old pos to zero if it doesn't delete front bar
//        if(pos_dot-1>pos_bar_front)
//        {
//            setOneLED(pos_dot-1,0);
//        }
        // check if dot is same pos as bar and update positions
        if(pos_dot==pos_bar_back)
        {
            pos_bar_back = pos_dot-1;
            pos_dot -= dot_delta;
        }
        //set bar
        setRange(pos_bar_back,led_count,cMax_brightness_);
        // render LEDs
        renderLEDs();
        //update position
        pos_dot++;
//        BOOST_LOG_TRIVIAL(debug) << "positions: dot=" << pos_dot << ", pos_bar=" << pos_bar_back << ", pos_bar_front=" << pos_bar_front;
    }
}

