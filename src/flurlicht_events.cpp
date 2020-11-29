#include "flurlicht_events.h"

#include <chrono>
#include <boost/thread/mutex.hpp>
#include <boost/log/trivial.hpp>


bool FLURLICHT_EVENTS::lockFront()
{ 
//    if (mutex_front_.try_lock())
//    {
//        any_mutex_locked = true;
//        BOOST_LOG_TRIVIAL(debug) << "mutex front locked";
//        return true;
//    }
//    BOOST_LOG_TRIVIAL(debug) << "mutex front unavailable";
//    return false;
    mutex_front_.lock();
    any_mutex_locked = true;
    BOOST_LOG_TRIVIAL(debug) << "mutex front locked";
    return true;
}

bool FLURLICHT_EVENTS::lockBack()
{
//    if (mutex_back_.try_lock())
//    {
//        any_mutex_locked = true;
//        BOOST_LOG_TRIVIAL(debug) << "mutex back locked";
//        return true;
//    }
//    BOOST_LOG_TRIVIAL(debug) << "mutex back unavailable";
//    return false;
    mutex_back_.lock();
    any_mutex_locked = true;
    BOOST_LOG_TRIVIAL(debug) << "mutex back locked";
    return true;
}

bool FLURLICHT_EVENTS::checkAnyLocked()
{
    return any_mutex_locked;
}

void FLURLICHT_EVENTS::unlockFront()
{
    mutex_front_.unlock();
    any_mutex_locked = false;
    BOOST_LOG_TRIVIAL(debug) << "mutex front unlocked";
}

void FLURLICHT_EVENTS::unlockBack()
{
    mutex_back_.unlock();
    any_mutex_locked = false;
    BOOST_LOG_TRIVIAL(debug) << "mutex back unlocked";
}

void FLURLICHT_EVENTS::unlockAll()
{
    unlockFront();
    unlockBack();
}
