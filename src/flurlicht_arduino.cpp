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

      // if \n is read, do processing
      if (c=='\n')
      {
          //process one line
          read(port_,buffer(&c,1));
          if(c=='0')
          {
              states_.front = false;
          }
          else if (c=='1')
          {
              states_.front = true;
          }
          //process next line
          read(port_,buffer(&c,1));
          if(c=='0')
          {
              states_.back = false;
          }
          else if (c=='1')
          {
              states_.back = true;
          }
          cout << "F:" << states_.front << " B:" << states_.back << endl;
          scanning = false;
          if (states_last_.back != states_.back)
          {
              BOOST_LOG_TRIVIAL(info) << "change detected! back level: " << states_.back << "," << states_last_.back;
//              updateStates(states_.back,BACK);
              states_last_.back = states_.back;
          };
          if(states_last_.front != states_.front)
          {
              BOOST_LOG_TRIVIAL(info) << "change detected! front level: " << states_.front << "," << states_last_.front;
//              updateStates(states_.front,FRONT);
              states_last_.front = states_.front;
          };
          updateStates(states_.back,BACK);
          updateStates(states_.front,FRONT);
      }
    }

}

void FLURLICHT_ARDUINO::clearBuffer()
{
    char c;

    for(auto i=0;i<=20;i++)
    {
        read(port_,buffer(&c,1));
    }
}

void FLURLICHT_ARDUINO::updateStates(bool value, sensor_dir_t dir)
{
    if (value == true)
    {
        if (dir == sensor_dir_t::FRONT)
        {
//            BOOST_LOG_TRIVIAL(debug) << "reset last trigger time front";
            last_trigger_time_front_=FLURLICHT_TOOLS::getTime();
            states_ext_.front=true;
        }
        else
        {
//            BOOST_LOG_TRIVIAL(debug) << "reset last trigger time back";
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
                BOOST_LOG_TRIVIAL(debug) << "clear trigger front";
                states_ext_.front=false;
            }
        }
        else
        {
            if (FLURLICHT_TOOLS::checkRenderTimeValid(last_trigger_time_back_,cCoolOffPeriod_))
            {
                BOOST_LOG_TRIVIAL(debug) << "clear trigger back";
                states_ext_.back=false;
            }
        }

    }
}

//bool FLURLICHT_ARDUINO::evalBool(char c)
//{
//    if(c=='0')
//    {
//        return
//    }
//}

void FLURLICHT_ARDUINO::runThread()
{
    clearBuffer();
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






