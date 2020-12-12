#ifndef FLURLICHT_ARDUINO_H
#define FLURLICHT_ARDUINO_H

#include <iostream>
#include <boost/asio.hpp>
#include "flurlicht_gpio.h"

class FLURLICHT_ARDUINO
{
public:
    FLURLICHT_ARDUINO();

    FLURLICHT_GPIO::sensor_states_dirs_t getSensorStates();
    void run();
private:
    boost::asio::io_service io_;
    boost::asio::serial_port port_;

    FLURLICHT_GPIO::sensor_states_dirs_t states_;

    bool evaluateTrigger(float voltage);
    void readOnce();
};

#endif // FLURLICHT_ARDUINO_H
