#include "animations_random_granular.h"
#include "flurlicht_tools.h"
#include <utility>
#include <iostream>


ANIMATION_RANDOM_GRANULAR::ANIMATION_RANDOM_GRANULAR(const std::shared_ptr<ws2811_t>& ledstring): ANIMATION(ledstring,6)
{
    BOOST_LOG_TRIVIAL(debug) << "ANIMATION_RANDOM_GRANULAR: constructor called";
//    initLEDPoolIterators(FADE_IN);
    initLEDPool(FADE_IN);
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
    // update LED until failcount is same as amount of LEDS
    auto limit = 1;
    while(!led_pool_.empty())
    {
        for(auto i=0;i<limit;i++)
        {
            if(!led_pool_.size()==0)
            {
                unsigned long led_id = rand() % led_pool_.size();
                auto step = led_pool_[led_id].second;
                if (direction==FADE_IN)
                {
                    step++;
                }
                else
                {
                    step--;
                }
                //set LED value
                setOneLED(led_pool_[led_id].first,getPWMValue(step));
                // delete element if stepsize was min or max
                if(step<=0)
                {
                    led_pool_.erase(led_pool_.begin()+led_id);
                }
                else if(step>=pwm_table_size)
                {
                    led_pool_.erase(led_pool_.begin()+led_id);
                }
                //update vector
                led_pool_[led_id].second = step;
            }
        }
        //render and update
        renderLEDs();
        //update limit
        limit++;
    }
    BOOST_LOG_TRIVIAL(debug) << "animation finished";
//    for(auto led=0;led<getLEDCount();led++)
//    {
//        std::cout << getOneLEDBrightness(led) << "|";
//    }
//     std::cout << std::endl;
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
    return led_pool_[led].second;
}

void ANIMATION_RANDOM_GRANULAR::setLEDStep(unsigned long led, pwm_steps_t step)
{
//    BOOST_LOG_TRIVIAL(debug) << "setting step of LED: " << led << "|" << step;
    led_pool_[led].second=step;
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

//void ANIMATION_RANDOM_GRANULAR::initLEDPoolIterators(ANIMATION::fades_t direction)
//{
//    for(auto led=0;led<getLEDCount();led++)
//    {
//        if (direction==FADE_IN)
//        {
//            led_pool_.push_back(1);
//        }
//        else
//        {
//            led_pool_.push_back(pwm_table_size-2);
//        }
//    }
//}

void ANIMATION_RANDOM_GRANULAR::initLEDPool(ANIMATION::fades_t direction)
{
    auto init = 0;
    if (direction==FADE_IN)
    {
        init = 1;
    }
    else
    {
        init = pwm_table_size-2;
    }

    //fill
    for(auto led=0;led<getLEDCount();led++)
    {
        auto buffer_pair = std::make_pair(led,init);
//        buffer_pair.first = led;
//        buffer_pair.second = step;
        led_pool_.push_back(buffer_pair);
    }
}
