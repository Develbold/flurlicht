#ifndef FLURLICHT_MQTT_H
#define FLURLICHT_MQTT_H

#include "mqtt/async_client.h"
#include <boost/log/trivial.hpp>

// classes taken from the paho example

const std::string SERVER_ADDRESS("tcp://192.168.0.12:1883");
const std::string CLIENT_ID("paho_cpp_async_subcribe");
const std::string TOPIC("homeassistant/binary_sensor/0010fa6e384a/pir_front/state");
const std::string USER("arduino");
const std::string PW("foobar");

const int	QOS = 1;
const int	N_RETRY_ATTEMPTS = 5;

// Callbacks for the success or failures of requested actions.
// This could be used to initiate further action, but here we just log the
// results to the console.

class mqtt_action_listener : public virtual mqtt::iaction_listener
{
    std::string name_;

    void on_failure(const mqtt::token& tok) override {
        BOOST_LOG_TRIVIAL(info) << name_ << "MQTT: failure";
        if (tok.get_message_id() != 0)
            BOOST_LOG_TRIVIAL(info) << "MQTT: for token: [" << tok.get_message_id() << "]";
    }

    void on_success(const mqtt::token& tok) override {
        BOOST_LOG_TRIVIAL(info) << name_ << "MQTT success";
        if (tok.get_message_id() != 0)
            BOOST_LOG_TRIVIAL(info) << "MQTT: for token: [" << tok.get_message_id() << "]";
        auto top = tok.get_topics();
        if (top && !top->empty())
            BOOST_LOG_TRIVIAL(info) << "MQTT: token topic: '" << (*top)[0] << "', ...";
    }

public:
    mqtt_action_listener(const std::string& name) : name_(name) {}
};


/**
 * Local callback & listener class for use with the client connection.
 * This is primarily intended to receive messages, but it will also monitor
 * the connection to the broker. If the connection is lost, it will attempt
 * to restore the connection and re-subscribe to the topic.
 */
class mqtt_callback : public virtual mqtt::callback,
                    public virtual mqtt::iaction_listener

{
    // Counter for the number of connection retries
    int nretry_;
    // The MQTT client
    mqtt::async_client& cli_;
    // Options to use if we need to reconnect
    mqtt::connect_options& connOpts_;
    // An action listener to display the result of actions.
    mqtt_action_listener subListener_;

    // This deomonstrates manually reconnecting to the broker by calling
    // connect() again. This is a possibility for an application that keeps
    // a copy of it's original connect_options, or if the app wants to
    // reconnect with different options.
    // Another way this can be done manually, if using the same options, is
    // to just call the async_client::reconnect() method.
    void reconnect() {
        std::this_thread::sleep_for(std::chrono::milliseconds(2500));
        try {
            cli_.connect(connOpts_, nullptr, *this);
        }
        catch (const mqtt::exception& exc) {
            BOOST_LOG_TRIVIAL(error) << "MQTT: Error: " << exc.what();
            exit(1);
        }
    }

    // Re-connection failure
    void on_failure(const mqtt::token& tok) override {
        BOOST_LOG_TRIVIAL(error) << "MQTT: Connection attempt failed";
        if (++nretry_ > N_RETRY_ATTEMPTS)
            exit(1);
        reconnect();
    }

    // (Re)connection success
    // Either this or connected() can be used for callbacks.
    void on_success(const mqtt::token& tok) override {}

    // (Re)connection success
    void connected(const std::string& cause) override {
        BOOST_LOG_TRIVIAL(info) << "MQTT: Connection success";
        BOOST_LOG_TRIVIAL(info) << "MQTT: Subscribing to topic '" << TOPIC << "'\n"
            << "\tfor client " << CLIENT_ID
            << " using QoS" << QOS << "\n"
            << "\nPress Q<Enter> to quit\n";

        cli_.subscribe(TOPIC, QOS, nullptr, subListener_);
    }

    // Callback for when the connection is lost.
    // This will initiate the attempt to manually reconnect.
    void connection_lost(const std::string& cause) override {
        BOOST_LOG_TRIVIAL(error) << "MQTT: Connection lost";
        if (!cause.empty())
            BOOST_LOG_TRIVIAL(error) << "MQTT: cause: " << cause;

        BOOST_LOG_TRIVIAL(info) << "MQTT: Reconnecting...";
        nretry_ = 0;
        reconnect();
    }

    // Callback for when a message arrives.
    void message_arrived(mqtt::const_message_ptr msg) override {
        BOOST_LOG_TRIVIAL(info) << "MQTT: Message arrived";
        BOOST_LOG_TRIVIAL(info) << "MQTT: topic: '" << msg->get_topic() << "'";
        BOOST_LOG_TRIVIAL(info) << "MQTT: payload: '" << msg->to_string() << "'\n";
    }

    void delivery_complete(mqtt::delivery_token_ptr token) override {}

public:
    mqtt_callback(mqtt::async_client& cli, mqtt::connect_options& connOpts)
                : nretry_(0), cli_(cli), connOpts_(connOpts), subListener_("Subscription") {}
};


class FLURLICHT_MQTT
{
public:
    FLURLICHT_MQTT();
    ~FLURLICHT_MQTT();
    bool run();
};

#endif // FLURLICHT_MQTT_H
