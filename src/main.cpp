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
    std::cout << "INFO: finished execution" << std::endl;
    return 0;
}
