#include "flurlicht_arduino.h"
#include "flurlicht_tools.h"
#include <sstream>
#include <boost/chrono.hpp>
#include <boost/thread.hpp>

using namespace::boost::asio;
using namespace std;


FLURLICHT_ARDUINO::FLURLICHT_ARDUINO(): port_(io_,"/dev/ttyUSB0")
{
    // Base serial settings
    serial_port_base::baud_rate BAUD(9600);
    serial_port_base::flow_control FLOW( serial_port_base::flow_control::none );
    serial_port_base::parity PARITY( serial_port_base::parity::none );
    serial_port_base::stop_bits STOP( serial_port_base::stop_bits::one );

    // create port
//    port_ = std::make_unique<serial_port>(io_,"/dev/ttyUSB0");
//    port_ = serial_port(io_,"/dev/ttyUSB0");

    // Setup port - base settings
    port_.set_option( BAUD );
    port_.set_option( FLOW );
    port_.set_option( PARITY );
    port_.set_option( STOP );

    last_trigger_time_front_= FLURLICHT_TOOLS::getTime();
    last_trigger_time_back_= FLURLICHT_TOOLS::getTime();

}

void FLURLICHT_ARDUINO::readOnce()
{
    char c;
    std::string line;
    bool scanning = true;

    while(scanning)
    {
      // read one byte
      read(port_,buffer(&c,1));
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
          // now convert from voltage to trigger
          states_.front = evaluateTrigger(v1);
          states_.back = evaluateTrigger(v2);
          line.clear();
          scanning = false;
          if (states_last_.back != states_.back)
          {
              //TODO add comm
              states_last_.back = states_.back;
          };
          if(states_last_.front != states_.front)
          {
              //TODO add comm
              states_last_.front = states_.front;
          };

      }
    }

}

void FLURLICHT_ARDUINO::updateStates(bool value, sensor_dir_t dir)
{
    if (value == true)
    {
        if (dir == sensor_dir_t::FRONT)
        {
            last_trigger_time_front_=FLURLICHT_TOOLS::getTime();
            states_ext_.front=true;
        }
        else
        {
            last_trigger_time_back_=FLURLICHT_TOOLS::getTime();
            states_ext_.back=true;
        }
    }
    else
    {
        if(dir == sensor_dir_t::FRONT)
        {
            if (FLURLICHT_TOOLS::checkRenderTimeValid(last_trigger_time_front_,cCoolOffPeriod_))
            {
                states_ext_.front=false;
            }
        }
        else
        {
            if (FLURLICHT_TOOLS::checkRenderTimeValid(last_trigger_time_back_,cCoolOffPeriod_))
            {
                states_ext_.back=false;
            }
        }

    }
}

void FLURLICHT_ARDUINO::runThread()
{
    while(true)
    {
        readOnce();
        boost::this_thread::sleep_for(boost::chrono::milliseconds{100});
    }
}

FLURLICHT_GPIO::sensor_states_dirs_t FLURLICHT_ARDUINO::getSensorStates()
{
    return states_ext_;

}

void FLURLICHT_ARDUINO::run()
{
    boost::thread* t = new boost::thread(boost::bind(&FLURLICHT_ARDUINO::runThread,this));
    t->detach();
}

bool FLURLICHT_ARDUINO::evaluateTrigger(float voltage)
{
    if (voltage > 2.5)
    {
        return true;
    }
    else
    {
        return false;
    }
}





