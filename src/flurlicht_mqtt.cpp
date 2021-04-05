#include "flurlicht_mqtt.h"
#include "mqtt/async_client.h"


#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <thread>
#include <chrono>
#include "mqtt/async_client.h"


/////////////////////////////////////////////////////////////////////////////

//// Callbacks for the success or failures of requested actions.
//// This could be used to initiate further action, but here we just log the
//// results to the console.

//class action_listener : public virtual mqtt::iaction_listener
//{
//    std::string name_;

//    void on_failure(const mqtt::token& tok) override {
//        std::cout << name_ << " failure";
//        if (tok.get_message_id() != 0)
//            std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
//        std::cout << std::endl;
//    }

//    void on_success(const mqtt::token& tok) override {
//        std::cout << name_ << " success";
//        if (tok.get_message_id() != 0)
//            std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
//        auto top = tok.get_topics();
//        if (top && !top->empty())
//            std::cout << "\ttoken topic: '" << (*top)[0] << "', ..." << std::endl;
//        std::cout << std::endl;
//    }

//public:
//    action_listener(const std::string& name) : name_(name) {}
//};

///////////////////////////////////////////////////////////////////////////////

///**
// * Local callback & listener class for use with the client connection.
// * This is primarily intended to receive messages, but it will also monitor
// * the connection to the broker. If the connection is lost, it will attempt
// * to restore the connection and re-subscribe to the topic.
// */
//class callback : public virtual mqtt::callback,
//                    public virtual mqtt::iaction_listener

//{
//    // Counter for the number of connection retries
//    int nretry_;
//    // The MQTT client
//    mqtt::async_client& cli_;
//    // Options to use if we need to reconnect
//    mqtt::connect_options& connOpts_;
//    // An action listener to display the result of actions.
//    action_listener subListener_;

//    // This deomonstrates manually reconnecting to the broker by calling
//    // connect() again. This is a possibility for an application that keeps
//    // a copy of it's original connect_options, or if the app wants to
//    // reconnect with different options.
//    // Another way this can be done manually, if using the same options, is
//    // to just call the async_client::reconnect() method.
//    void reconnect() {
//        std::this_thread::sleep_for(std::chrono::milliseconds(2500));
//        try {
//            cli_.connect(connOpts_, nullptr, *this);
//        }
//        catch (const mqtt::exception& exc) {
//            std::cerr << "Error: " << exc.what() << std::endl;
//            exit(1);
//        }
//    }

//    // Re-connection failure
//    void on_failure(const mqtt::token& tok) override {
//        std::cout << "Connection attempt failed" << std::endl;
//        if (++nretry_ > N_RETRY_ATTEMPTS)
//            exit(1);
//        reconnect();
//    }

//    // (Re)connection success
//    // Either this or connected() can be used for callbacks.
//    void on_success(const mqtt::token& tok) override {}

//    // (Re)connection success
//    void connected(const std::string& cause) override {
//        std::cout << "\nConnection success" << std::endl;
//        std::cout << "\nSubscribing to topic '" << TOPIC << "'\n"
//            << "\tfor client " << CLIENT_ID
//            << " using QoS" << QOS << "\n"
//            << "\nPress Q<Enter> to quit\n" << std::endl;

//        cli_.subscribe(TOPIC, QOS, nullptr, subListener_);
//    }

//    // Callback for when the connection is lost.
//    // This will initiate the attempt to manually reconnect.
//    void connection_lost(const std::string& cause) override {
//        std::cout << "\nConnection lost" << std::endl;
//        if (!cause.empty())
//            std::cout << "\tcause: " << cause << std::endl;

//        std::cout << "Reconnecting..." << std::endl;
//        nretry_ = 0;
//        reconnect();
//    }

//    // Callback for when a message arrives.
//    void message_arrived(mqtt::const_message_ptr msg) override {
//        std::cout << "Message arrived" << std::endl;
//        std::cout << "\ttopic: '" << msg->get_topic() << "'" << std::endl;
//        std::cout << "\tpayload: '" << msg->to_string() << "'\n" << std::endl;
//    }

//    void delivery_complete(mqtt::delivery_token_ptr token) override {}

//public:
//    callback(mqtt::async_client& cli, mqtt::connect_options& connOpts)
//                : nretry_(0), cli_(cli), connOpts_(connOpts), subListener_("Subscription") {}
//};

/////////////////////////////////////////////////////////////////////////////





bool FLURLICHT_MQTT::parsePayload(std::string msg)
{
    if (msg.compare("ON") == 0)
    {
        return false;
    }
    else if (msg.compare("OFF") == 0)
    {
        return true;
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

