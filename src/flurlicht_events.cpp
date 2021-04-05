#include "flurlicht_events.h"
#include "flurlicht_tools.h"
#include <boost/log/trivial.hpp>

FLURLICHT_EVENTS::FLURLICHT_EVENTS()
{

}

// set last trigger time to now
void FLURLICHT_EVENTS::resetTrigger()
{
    BOOST_LOG_TRIVIAL(debug) << "OCCUPANCY: reset trigger";
    lock_.lock();
    last_trigger_time_ = FLURLICHT_TOOLS::getTime();
    lock_.unlock();
}

// if last time triggered is bigger then occupancy time, set occupancy to true
bool FLURLICHT_EVENTS::getOccupancy()
{
    lock_.lock();
    bool buffer = FLURLICHT_TOOLS::checkRenderTimeValid(last_trigger_time_,cOccupancyTime_);
    lock_.unlock();
    return buffer;
}
