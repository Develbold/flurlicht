#include "flurlicht.h"
#include "flurlicht_mqtt.h"
#include <iostream>

auto main() -> int
{
    BOOST_LOG_TRIVIAL(info) << "Flurlicht started";

//    flurlicht foo;
//    foo.run();
    FLURLICHT_MQTT mqtt;
    mqtt.run();

    std::cout << "INFO: finished execution" << std::endl;
    return 0;
}
