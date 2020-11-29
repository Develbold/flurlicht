#include "flurlicht_events.h"

#include <chrono>
#include <boost/thread/mutex.hpp>


bool FLURLICHT_EVENTS::lockFront()
{ 
    if (mutex_front_.try_lock())
    {
        return true;
    }
    return false;
}

bool FLURLICHT_EVENTS::lockBack()
{
    if (mutex_back_.try_lock())
    {
        return true;
    }
    return false;
}

void FLURLICHT_EVENTS::unlockFront()
{
    mutex_front_.unlock();
}

void FLURLICHT_EVENTS::unlockBack()
{
    mutex_back_.unlock();
}

void FLURLICHT_EVENTS::unlockAll()
{
    unlockFront();
    unlockBack();
}
