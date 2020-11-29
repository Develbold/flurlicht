#include "flurlicht_tools.h"
#include <iostream>
#include <chrono>
#include <thread>


using namespace std;

void FLURLICHT_TOOLS::sleepPeriod(int period)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(period));
}
