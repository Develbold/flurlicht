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

void ANIMATION_SCANNER::render(fades_t direction)
{
    auto pos_dot = 0;
    auto pos_bar = getLEDCount();
    while(pos_bar==0)
    {
        // set new postition
        setOneLED(pos_dot,cMax_brightness_);
        // set old pos to zero
        setOneLED(pos_dot-1,0);
        // check if dot is same pos as bar
        if(pos_dot==pos_bar)
        {
            pos_bar = pos_dot;
            pos_dot = 0;
        }
        // render LEDs
        renderLEDs();
        //update postition
        pos_dot++;
    }
}

