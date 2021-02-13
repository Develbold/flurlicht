#include "animations_random_granular.h"
#include "flurlicht_tools.h"
#include <utility>
#include <iostream>


ANIMATION_RANDOM_GRANULAR::ANIMATION_RANDOM_GRANULAR(const std::shared_ptr<ws2811_t>& ledstring): ANIMATION(ledstring)
{
    BOOST_LOG_TRIVIAL(debug) << "ANIMATION_RANDOM_GRANULAR: constructor called";
    setTimeDelta(6);
    initLEDPoolIterators(FADE_IN);
//    for(auto led=0;led<ledstring->channel[0].count;led++)
//    {
//        led_pool_.push_back(led);
//    }
//    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

//    shuffle (led_pool_.begin(), led_pool_.end(), std::default_random_engine(seed));

}

ANIMATION_RANDOM_GRANULAR::~ANIMATION_RANDOM_GRANULAR()
{
    //~ANIMATION();
}

////TODO use iterators instead of array access
//void ANIMATION_RANDOM_GRANULAR::render(ANIMATION::fades_t direction)
//{
//    unsigned long led_count = 1;
//    //auto limit = 0;
//    while(!led_pool_.empty())
//    {
//        if (FLURLICHT_TOOLS::checkRenderTimeValid(last_render_time_,getTimeDelta()))
//        {
//            //if led count is greater then vector size, set it to vector size
//            if (led_count>=led_pool_.size())
//            {
//                led_count = led_pool_.size();;
//            }
//            for(unsigned long i=0;i<=led_count;i++)
//            {
//                updateLEDBufferOnceRandomly(direction);
//            }
//            //increase amount of leds to be rendered
//            led_count++;
//            // render and update
//            renderLEDs();
//            BOOST_LOG_TRIVIAL(debug) << "LED count: " << led_count <<"|"<<led_pool_.size();
//            resetLastRenderTime();
//        }
//    }
//    BOOST_LOG_TRIVIAL(debug) << "no more LEDs available, animation finished";
//    for(auto led=0;led<getLEDCount();led++)
//    {
//        std::cout << getOneLEDBrightness(led) << "|";
//    }
//     std::cout << std::endl;
//}

//TODO use iterators instead of array access
void ANIMATION_RANDOM_GRANULAR::render(ANIMATION::fades_t direction)
{
    auto fail_count = 1;
    //auto limit = 0;
    // update LED until failcount is same as amount of LEDS
    auto y = 1;
    while(fail_count!=getLEDCount())
    {
        auto i=0;
        while(i<=y)
        {
            if(!updateLEDBufferOnceRandomly(direction))
            {
                fail_count++;
            }
            else
            {
                i++;
            }
        }
        y++;
        BOOST_LOG_TRIVIAL(debug) << "LED y: " << y << "|" << fail_count;
        //render and update
        renderLEDs();
    }
    BOOST_LOG_TRIVIAL(debug) << "animation finished";
    for(auto led=0;led<getLEDCount();led++)
    {
        std::cout << getOneLEDBrightness(led) << "|";
    }
     std::cout << std::endl;
}



//TODO improve handling of reading from empty pool
//choose one random LED and update the Render Buffer
bool ANIMATION_RANDOM_GRANULAR::updateLEDBufferOnceRandomly(ANIMATION::fades_t direction)
{
    // get a random led id
    unsigned long led_id = rand() % led_pool_.size();
    if(checkValidLEDToChangeStep(led_id))
    {
        // get the step for led_id
        pwm_steps_t step = getLEDStep(led_id);
        //increase or decrease step
        if (direction==FADE_IN)
        {
            step++;
        }
        else
        {
            step--;
        }
        // store new step value
        setLEDStep(led_id,step);
        // set led brightness
        setOneLED(led_id,getPWMValue(step));
//        //render and update
//        renderLEDs();
//        BOOST_LOG_TRIVIAL(debug) << "LED updated: " << led_id <<"|"<<step;
        return true;
    }
    else
    {
//        BOOST_LOG_TRIVIAL(debug) << "LED not updated: " << led_id;
        return true;
    }
}

ANIMATION::pwm_steps_t ANIMATION_RANDOM_GRANULAR::getLEDStep(unsigned long led)
{
//    BOOST_LOG_TRIVIAL(debug) << "reading step of LED: " << led;
    return led_pool_.at(led);
}

void ANIMATION_RANDOM_GRANULAR::setLEDStep(unsigned long led, pwm_steps_t step)
{
//    BOOST_LOG_TRIVIAL(debug) << "setting step of LED: " << led << "|" << step;
    led_pool_[led]=step;
}

// return false if LED's step is either at 0 or full (=pwmtable_.size())
bool ANIMATION_RANDOM_GRANULAR::checkValidLEDToChangeStep(unsigned long id)
{
    auto buffer = getLEDStep(id);
    if (buffer>=0||buffer<=pwm_table_size)
    {
//        BOOST_LOG_TRIVIAL(debug) << "LED invalid: " << id << "|" << buffer;
        return false;
    }
    else
    {
//        BOOST_LOG_TRIVIAL(debug) << "LED valid: " << id;
        return true;
    }
}

void ANIMATION_RANDOM_GRANULAR::initLEDPoolIterators(ANIMATION::fades_t direction)
{
    for(auto led=0;led<getLEDCount();led++)
    {
        if (direction==FADE_IN)
        {
            led_pool_.push_back(1);
        }
        else
        {
            led_pool_.push_back(pwm_table_size-2);
        }
    }
}

//void ANIMATION_RANDOM_GRANULAR::initLEDPool()
//{
//    typedef std::pair<int,uint8_t> pair_t;
//    auto buffer_size = getLEDCount();
//    std::vector<uint8_t> buffer_steps(buffer_size);
//    std::vector<uint8_t> buffer_leds(buffer_size);
//    for(auto led=0;led<getLEDCount();led++)
//    {
//        buffer_leds.push_back(led);
//    }
//    while(!buffer_leds.empty())
//    {
//        auto led = rand() % buffer_leds.size();
//        auto led_id = buffer_leds.at(led);
//        auto step = buffer_steps.at(led_id);
//        pair_t buffer = std::make_pair(led_id,step);

//    }
//}
