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
    auto pos_bar_back = getLEDCount();
    auto pos_bar_front = 0;
    while(pos_bar_front!=pos_bar_back)
    {
        // set new postition
        setOneLED(pos_dot,cMax_brightness_);
        // set old pos to zero if it doesnt delete front bar
        if(pos_dot-1>pos_bar_front)
        {
            setOneLED(pos_dot-1,0);
        }
        // check if dot is same pos as bar and update positions
        if(pos_dot==pos_bar_back)
        {
            pos_bar_back = pos_dot-1;
            pos_dot = pos_bar_front;
            pos_bar_front++;
        }
        // render LEDs
        renderLEDs();
        //update postition
        pos_dot++;
//        BOOST_LOG_TRIVIAL(debug) << "positions: dot=" << pos_dot << ", pos_bar=" << pos_bar_back << ", pos_bar_front=" << pos_bar_front;
    }
}

