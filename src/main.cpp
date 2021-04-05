#include "flurlicht.h"
#include "flurlicht_mqtt.h"
#include <iostream>

auto main() -> int
{
    BOOST_LOG_TRIVIAL(info) << "Flurlicht started";

    try
    {
        flurlicht foo;
        foo.run();
    }  catch (...)
    {
        BOOST_LOG_TRIVIAL(info) << "Flurlicht was stopped due to unknown error";
    }
    std::shared_ptr<FLURLICHT_EVENTS> occupancy = std::make_shared<FLURLICHT_EVENTS>();
//    FLURLICHT_MQTT mqtt(occupancy, "homeassistant/binary_sensor/0010fa6e384a/pir_front/state");
//    FLURLICHT_MQTT mqtt2(occupancy, "homeassistant/binary_sensor/0010fa6e384a/pir_back/state");
//    mqtt.run();
//    mqtt2.run();

//    sleep(30);
    std::cout << "INFO: finished execution" << std::endl;
    return 0;
}
