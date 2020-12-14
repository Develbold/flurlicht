#include "flurlicht_tools.h"
#include <iostream>
#include <thread>


using namespace std;

void FLURLICHT_TOOLS::sleepPeriod(int period)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(period));
}

auto FLURLICHT_TOOLS::getTime() -> std::chrono::high_resolution_clock::time_point
{
    return std::chrono::high_resolution_clock::now();
}

auto FLURLICHT_TOOLS::checkRenderTimeValid(std::chrono::high_resolution_clock::time_point last_render_time, int delta) -> bool
{
    //check if it is time to render
    auto time_delta = std::chrono::duration_cast<std::chrono::milliseconds>(FLURLICHT_TOOLS::getTime() - last_render_time);

    return time_delta.count()>delta;
}
