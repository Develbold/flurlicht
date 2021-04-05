#include "flurlicht_occupancy.h"
#include "flurlicht_tools.h"
#include <boost/log/trivial.hpp>

FLURLICHT_OCCUPANCY::FLURLICHT_OCCUPANCY()
{
    BOOST_LOG_TRIVIAL(debug) << "FLURLICHT_OCCUPANCY::FLURLICHT_OCCUPANCY";
    resetTrigger();
}

FLURLICHT_OCCUPANCY::~FLURLICHT_OCCUPANCY()
{
    BOOST_LOG_TRIVIAL(debug) << "FLURLICHT_OCCUPANCY::~FLURLICHT_OCCUPANCY";
}

// set last trigger time to now
void FLURLICHT_OCCUPANCY::resetTrigger()
{
    BOOST_LOG_TRIVIAL(debug) << "OCCUPANCY: reset trigger";
    lock_.lock();
    last_trigger_time_ = FLURLICHT_TOOLS::getTime();
    lock_.unlock();
}

// if last time triggered is bigger then occupancy time, set occupancy to true
bool FLURLICHT_OCCUPANCY::getOccupancy()
{
    lock_.lock();
    bool buffer = !FLURLICHT_TOOLS::checkRenderTimeValid(last_trigger_time_,cOccupancyTime_);
    BOOST_LOG_TRIVIAL(debug) << "OCCUPANCY: " << buffer;
    lock_.unlock();
    return buffer;
}
