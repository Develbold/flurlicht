#ifndef FLURLICHT_EVENTS_H
#define FLURLICHT_EVENTS_H

#include <boost/thread/mutex.hpp>

class FLURLICHT_EVENTS
{
public:
    FLURLICHT_EVENTS();
    void resetTrigger();
    bool getOccupancy();
private:
    boost::mutex lock_;
    std::chrono::high_resolution_clock::time_point last_trigger_time_;
    const int cOccupancyTime_ = 5000;

//    bool getTriggerValidity();
};

#endif // FLURLICHT_EVENTS_H
