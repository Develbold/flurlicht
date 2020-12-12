#ifndef FLURLICHT_TOOLS_H
#define FLURLICHT_TOOLS_H

#include <chrono>

class FLURLICHT_TOOLS
{
public:
    static void sleepPeriod(int period);
    static std::chrono::high_resolution_clock::time_point getTime();
    static bool checkRenderTimeValid(std::chrono::high_resolution_clock::time_point last_render_time, int delta);
};



#endif // FLURLICHT_TOOLS_H
