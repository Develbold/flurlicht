#include <iostream>
#include "flurlicht.h"


using namespace std;





int main()
{
    BOOST_LOG_TRIVIAL(info) << "Flurlicht started";

    flurlicht foo;
    foo.run();

    cout << "INFO: finished execution" << endl;
    return 0;
}
