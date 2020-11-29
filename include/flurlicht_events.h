#ifndef FLURLICHT_EVENTS_H
#define FLURLICHT_EVENTS_H

#include <iostream>
#include <boost/thread.hpp>


class FLURLICHT_EVENTS
{
public:
    bool lockFront();
    bool lockBack();
    void unlockAll();
private:
    void unlockFront();
    void unlockBack();
    boost::mutex mutex_front_;
    boost::mutex mutex_back_;
};

#endif // FLURLICHT_EVENTS_H
