//#include "flurlicht.h"
//#include <iostream>


#include <iostream>
#include <boost/asio.hpp>
#include <sstream>
//#include<string.h>
using namespace::boost::asio;
using namespace std;

#define PORT "/dev/ttyUSB0"

// Base serial settings
serial_port_base::baud_rate BAUD(9600);
serial_port_base::flow_control FLOW( serial_port_base::flow_control::none );
serial_port_base::parity PARITY( serial_port_base::parity::none );
// serial_port_base::stop_bits STOP( serial_port_base::stop_bits::one );
serial_port_base::stop_bits STOP( serial_port_base::stop_bits::one );

int main(){
  io_service io;
  serial_port port( io, PORT );

  // Setup port - base settings
  port.set_option( BAUD );
  port.set_option( FLOW );
  port.set_option( PARITY );
  port.set_option( STOP );

  stringstream ss;
  char c;
  std::string line;
  while(1)
  {
    // read one byte
    read(port,buffer(&c,1));
    // insert into line
    line.insert(line.end(),1,c);

    //cout << line << " size: " << line.size() << endl;
    //cout << "-" << endl;

    // if \n is read, do processing
    if (c=='\n' && line.size() >= 10)
    {
        unsigned first = line.find('A');
        unsigned middle = line.find('B');
        unsigned end = line.find('\n');
        float v1 = stof(line.substr(first+1,middle-first-1));
        float v2 = stof(line.substr(middle+1,end-middle-1));
        cout << "V1:" << v1 << " V2:" << v2 << endl;
        line.clear();
    }
  }

  return 0;
}

//#include <stdio.h>
//#include <string.h>

//char serialPortFilename[] = "/dev/ttyUSB0";

//int main()
//{
//    char readBuffer[1024];
//    int numBytesRead;

//    FILE *serPort = fopen(serialPortFilename, "r");

//    if (serPort == NULL)
//    {
//        printf("ERROR");
//        return 0;
//    }

//    printf(serialPortFilename);
//    printf(":\n");
//    while(1)
//    {
//        memset(readBuffer, 0, 1024);
//        fread(readBuffer, sizeof(char),1024,serPort);
//        if(sizeof(readBuffer) != 0)
//        {
//            printf(readBuffer);
//        }
//        sleep(1);
//    }
//    return 0;
//}




//int main()
//{
//    BOOST_LOG_TRIVIAL(info) << "Flurlicht started";

//    flurlicht foo;
//    foo.run();

//    cout << "INFO: finished execution" << endl;
//    return 0;
//}
