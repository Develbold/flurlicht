#include <iostream>
#include "flurlicht.h"


using namespace std;

extern "C" {
#include <mqueue.h>
#include "UUGear/RaspberryPi/src/UUGear.h"
}



int main()
{
    BOOST_LOG_TRIVIAL(info) << "Flurlicht started";

//    flurlicht foo;
//    foo.run();

    UUGearDevice arduino;

    setupUUGear();

    setShowLogs(1);

    arduino = attachUUGearDevice ("UUGear-Arduino-7853-2668");

    cout << "INFO: finished execution" << endl;
    return 0;
}
