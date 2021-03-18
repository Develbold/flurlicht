#ifndef FLURLICHT_EVENTS_H
#define FLURLICHT_EVENTS_H

#include <iostream>
#include <boost/thread.hpp>


class FLURLICHT_EVENTS
{
public:
    bool lockFront();
    bool lockBack();
    bool checkAnyLocked();
    void unlockAll();
    void unlockAllQueued();
private:
    void unlockFront();
    void unlockBack();
    bool any_mutex_locked = false;
    boost::mutex mutex_front_;
    boost::mutex mutex_back_;
};

#endif // FLURLICHT_EVENTS_H
