#ifndef FLURLICHT_ARDUINO_H
#define FLURLICHT_ARDUINO_H

#include <iostream>
#include <boost/asio.hpp>
#include "flurlicht_gpio.h"
#include <boost/thread.hpp>

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
    FLURLICHT_GPIO::sensor_states_dirs_t states_ext_;
    FLURLICHT_GPIO::sensor_states_dirs_t states_last_;

    std::chrono::high_resolution_clock::time_point last_trigger_time_front_;
    std::chrono::high_resolution_clock::time_point last_trigger_time_back_;

    typedef enum {FRONT,BACK} sensor_dir_t;

    boost::mutex mutex_;

    const int cCoolOffPeriod_ = 5000;
    const int cBaudRate_ = 9600;

    bool evaluateTrigger(float voltage);
    void readOnce();
    void clearBuffer();
    void runThread();
    void updateStates(bool value, sensor_dir_t dir);
    bool evalBool(char c);
};

#endif // FLURLICHT_ARDUINO_H
