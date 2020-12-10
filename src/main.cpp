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

    arduino = attachUUGearDevice ((char *)"UUGear-Arduino-7853-2668");

    while(true)
    {
        if(arduino.fd != -1)
        {
            int pin0 = 0;	// analog input pin 3
            int pin1 = 1;	// analog input pin 3

            int value0,value1;
            float voltage0,voltage1;
            value0 = analogRead(&arduino, pin0);
            value1 = analogRead(&arduino, pin1);

            voltage0 = (float)(value0 * 5) / 1024;
            voltage1 = (float)(value0 * 5) / 1024;

            printf("%.2fV and %.2fV\n", voltage0,voltage1);
        }
    }

    cout << "INFO: finished execution" << endl;
    return 0;
}
