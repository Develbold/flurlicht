#include "flurlicht.h"
#include "flurlicht_mqtt.h"
#include <iostream>

namespace logging = boost::log;

auto main() -> int
{
    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::info
    );
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
