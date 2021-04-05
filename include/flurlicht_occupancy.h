#ifndef FLURLICHT_EVENTS_H
#define FLURLICHT_EVENTS_H

#include <boost/thread/mutex.hpp>
#include <chrono>

class FLURLICHT_OCCUPANCY
{
public:
    FLURLICHT_OCCUPANCY();
    ~FLURLICHT_OCCUPANCY();
    void resetTrigger();
    bool getOccupancy();
private:
    boost::mutex lock_;
    std::chrono::high_resolution_clock::time_point last_trigger_time_;
    const int cOccupancyTime_ = 5000;
};

#endif // FLURLICHT_EVENTS_H
