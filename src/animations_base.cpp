#include "animations_base.h"

std::chrono::high_resolution_clock::time_point ANIMATION::getTime()
{
    return std::chrono::high_resolution_clock::now();
}

auto ANIMATION::getStepSize()
{
    return step_size_;
}

auto ANIMATION::calcMaxSteps()
{
    return cMax_brightness_/getStepSize();
}

auto ANIMATION::getCurrentStep()
{
    return current_step_;
}

ANIMATION::led_t ANIMATION::calcNextBrightness()
{
    return getStepSize()*getCurrentStep();
}

ANIMATION::ANIMATION(std::shared_ptr<ws2811_t> ledstring)
{
    ledstring_ = ledstring;
    last_render_time_ = getTime();
    step_size_ = getStepSize();
    max_steps_ = calcMaxSteps();
    BOOST_LOG_TRIVIAL(debug) << "maximum number of steps: " << max_steps_;
}

ANIMATION::~ANIMATION()
{

}
