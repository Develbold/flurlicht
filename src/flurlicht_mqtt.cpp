#include "flurlicht_mqtt.h"
#include "mqtt/async_client.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>


bool FLURLICHT_MQTT::parsePayload(std::string msg)
{
    if (msg.compare("ON") == 0)
    {
        return true;
    }
    else if (msg.compare("OFF") == 0)
    {
        return false;
    }
    else
    {
        throw "unknown payload";
    }
}

bool FLURLICHT_MQTT::createSensorCallback(std::string topic)
{
    BOOST_LOG_TRIVIAL(debug) << "MQTT: creating Callback";
    // register callback
    BOOST_LOG_TRIVIAL(debug) << "MQTT: set callback";
    cli_->set_callback(*cb_);

    BOOST_LOG_TRIVIAL(debug) << "MQTT: try connection";
    try {
       BOOST_LOG_TRIVIAL(info) << "MQTT: Connecting to the MQTT server...";
       cli_->connect(*connOpts_, nullptr, *cb_);
    }
    catch (const mqtt::exception& exc) {
        BOOST_LOG_TRIVIAL(error) << "MQTT: Unable to connect to MQTT server: '"
            << SERVER_ADDRESS << "'" << exc;
        return false;
    }

    BOOST_LOG_TRIVIAL(debug) << "MQTT: done creating sensor callback";
    return true;
}

void FLURLICHT_MQTT::mqtt_callback::reconnect() {
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    try {
        cli_.connect(connOpts_, nullptr, *this);
    }
    catch (const mqtt::exception& exc) {
        BOOST_LOG_TRIVIAL(error) << "MQTT: Error: " << exc.what();
        exit(1);
    }
}

void FLURLICHT_MQTT::mqtt_callback::on_failure(const mqtt::token &tok) {
    BOOST_LOG_TRIVIAL(error) << "MQTT: Connection attempt failed";
    if (++nretry_ > N_RETRY_ATTEMPTS)
        exit(1);
    reconnect();
}

void FLURLICHT_MQTT::mqtt_callback::connected(const std::string &cause) {
    for(auto it=parent.TOPICS.begin();it!=parent.TOPICS.end();++it)
    {
        BOOST_LOG_TRIVIAL(info) << "MQTT: Connection success";
        BOOST_LOG_TRIVIAL(info) << "MQTT: Subscribing to topic '" << *it << "'\n"
                                << "\tfor client " << parent.CLIENT_ID
                                << " using QoS" << QOS;

        cli_.subscribe(*it, QOS, nullptr, subListener_);
    }
}

void FLURLICHT_MQTT::mqtt_callback::connection_lost(const std::string &cause) {
    BOOST_LOG_TRIVIAL(error) << "MQTT: Connection lost";
    if (!cause.empty())
        BOOST_LOG_TRIVIAL(error) << "MQTT: cause: " << cause;

    BOOST_LOG_TRIVIAL(info) << "MQTT: Reconnecting...";
    nretry_ = 0;
    reconnect();
}

void FLURLICHT_MQTT::mqtt_callback::message_arrived(mqtt::const_message_ptr msg) {
    BOOST_LOG_TRIVIAL(info) << "MQTT: Message arrived";
    BOOST_LOG_TRIVIAL(info) << "MQTT: topic: '" << msg->get_topic() << "'";
    BOOST_LOG_TRIVIAL(info) << "MQTT: payload: '" << msg->to_string() << "'\n";

    if(FLURLICHT_MQTT::parsePayload(msg->to_string()))
    {
        parent.occupancy_->resetTrigger();
    }
}

void FLURLICHT_MQTT::mqtt_action_listener::on_failure(const mqtt::token &tok) {
    BOOST_LOG_TRIVIAL(info) << name_ << "MQTT: failure";
    if (tok.get_message_id() != 0)
        BOOST_LOG_TRIVIAL(info) << "MQTT: for token: [" << tok.get_message_id() << "]";
}

void FLURLICHT_MQTT::mqtt_action_listener::on_success(const mqtt::token &tok) {
    BOOST_LOG_TRIVIAL(info) << name_ << "MQTT success";
    if (tok.get_message_id() != 0)
        BOOST_LOG_TRIVIAL(info) << "MQTT: for token: [" << tok.get_message_id() << "]";
    auto top = tok.get_topics();
    if (top && !top->empty())
        BOOST_LOG_TRIVIAL(info) << "MQTT: token topic: '" << (*top)[0] << "', ...";
}

FLURLICHT_MQTT::FLURLICHT_MQTT(std::shared_ptr<FLURLICHT_EVENTS> occupancy)
{
    BOOST_LOG_TRIVIAL(debug) << "MQTT: FLURLICHT_MQTT::FLURLICHT_MQTT";

    occupancy_ = occupancy;
    cli_ = std::make_shared<mqtt::async_client>(SERVER_ADDRESS, CLIENT_ID);
    connOpts_ = std::make_shared<mqtt::connect_options>(USER,PW);
    connOpts_->set_clean_session(false);
//    connOpts_->set_connect_timeout(5);

    cb_ = std::make_shared<mqtt_callback>(*this, *cli_, *connOpts_);
    BOOST_LOG_TRIVIAL(debug) << "MQTT: FLURLICHT_MQTT::FLURLICHT_MQTT done";
}

