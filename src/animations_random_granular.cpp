#include "animations_random_granular.h"
#include "flurlicht_tools.h"
#include <utility>


ANIMATION_RANDOM_GRANULAR::ANIMATION_RANDOM_GRANULAR(const std::shared_ptr<ws2811_t>& ledstring): ANIMATION(ledstring)
{
    BOOST_LOG_TRIVIAL(debug) << "ANIMATION_RANDOM_GRANULAR: constructor called";
    setTimeDelta(6);
    initLEDPoolIterators(FADE_IN);
    pwmtable_={0, 1, 2, 2, 2, 3, 3, 4, 5, 6, 7, 8, 10, 11, 13, 16, 19, 23, 27, 32, 38, 45, 54, 64, 76, 91, 108, 128, 152, 181, 215, 255};
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

//TODO use iterators instead of array access
void ANIMATION_RANDOM_GRANULAR::render(ANIMATION::fades_t direction)
{
    unsigned long led_count = 1;
    //auto limit = 0;
    while(!led_pool_.empty())
    {
        if (FLURLICHT_TOOLS::checkRenderTimeValid(last_render_time_,getTimeDelta()))
        {
            //if led count is greater then vector size, set it to vector size
            if (led_count>=led_pool_.size())
            {
                led_count = led_pool_.size();;
            }
            for(unsigned long i=0;i<=led_count;i++)
            {
                updateLEDBufferOnceRandomly(direction);
            }
            //increase amount of leds to be rendered
            led_count++;
            // render and update
            renderLEDs();
            BOOST_LOG_TRIVIAL(debug) << "LED count: " << led_count <<"|"<<led_pool_.size();
            resetLastRenderTime();
        }
    }
    BOOST_LOG_TRIVIAL(debug) << "no more LEDs available, animation finished";
}

//TODO improve handling of reading from empty pool
//choose one random LED and update the Render Buffer
bool ANIMATION_RANDOM_GRANULAR::updateLEDBufferOnceRandomly(ANIMATION::fades_t direction)
{
    if (led_pool_.size()!=0)
    {
        // get a random led id
        unsigned long led_id = rand() % led_pool_.size();
        // get the step for led_id
        pwm_steps_t step = led_pool_.at(led_id);
        if (direction==FADE_IN)
        {
            step++;
            if (step >= pwmtable_.size())
            {
                led_pool_.erase(led_pool_.begin()+led_id);
                BOOST_LOG_TRIVIAL(debug) << "erased: " << led_id;
                step=pwmtable_.size()-1;
            }
            else
            {
                // store current step
                led_pool_[led_id]=step;
            }
        }
        else
        {
            step--;
            if (step <= 0)
            {
                led_pool_.erase(led_pool_.begin()+led_id);
                BOOST_LOG_TRIVIAL(debug) << "erased: " << led_id;
                step=0;
            }
            else
            {
                // store current step
                led_pool_[led_id]=step;
            }
        }
        // set led brightness
        setOneLED(led_id,pwmtable_.at(step));
        BOOST_LOG_TRIVIAL(debug) << "LED: " << led_id <<"|"<<step<<"|"<<pwmtable_.at(step)<<"|"<<led_pool_.size();
        return true;
    }
    else
    {
        BOOST_LOG_TRIVIAL(info) << "recieved empty pool, returning false";
        return false;
    }

}

void ANIMATION_RANDOM_GRANULAR::initLEDPoolIterators(ANIMATION::fades_t direction)
{
    for(auto led=0;led<getLEDCount();led++)
    {
        if (direction==FADE_IN)
        {
            led_pool_.push_back(0);
        }
        else
        {
            led_pool_.push_back(pwmtable_.size()-1);
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
