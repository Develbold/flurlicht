#include "flurlicht.h"
#include <iostream>

auto main() -> int
{
    BOOST_LOG_TRIVIAL(info) << "Flurlicht started";

    flurlicht foo;
    foo.run();

    std::cout << "INFO: finished execution" << std::endl;
    return 0;
}
