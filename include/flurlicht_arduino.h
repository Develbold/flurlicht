#ifndef FLURLICHT_ARDUINO_H
#define FLURLICHT_ARDUINO_H

#include <iostream>
#include <boost/asio.hpp>
#include "flurlicht_gpio.h"

class FLURLICHT_ARDUINO
{
public:
    FLURLICHT_ARDUINO();
    void readOnce();

    FLURLICHT_GPIO::sensor_states_dirs_t getSensorStates();
private:
    boost::asio::io_service io_;
//    std::unique_ptr<boost::asio::serial_port> port_;
    boost::asio::serial_port port_;

    FLURLICHT_GPIO::sensor_states_dirs_t states_;

    bool evaluateTrigger(float voltage);
};

#endif // FLURLICHT_ARDUINO_H
