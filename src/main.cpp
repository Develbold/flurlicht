#include "flurlicht.h"
#include "flurlicht_mqtt.h"
#include <iostream>

auto main() -> int
{
    BOOST_LOG_TRIVIAL(info) << "Flurlicht started";

//    flurlicht foo;
//    foo.run();
    std::shared_ptr<FLURLICHT_EVENTS> occupancy = std::make_shared<FLURLICHT_EVENTS>();
    FLURLICHT_MQTT mqtt(occupancy);
    mqtt.run();

    std::cout << "INFO: finished execution" << std::endl;
    return 0;
}
