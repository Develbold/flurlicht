#ifndef FLURLICHT_MQTT_H
#define FLURLICHT_MQTT_H

//#define _GLIBCXX_USE_CXX11_ABI 0

#include "mqtt/async_client.h"
#include <boost/log/trivial.hpp>
#include "flurlicht_occupancy.h"

class FLURLICHT_MQTT
{
public:
    FLURLICHT_MQTT(std::shared_ptr<FLURLICHT_OCCUPANCY> occupancy);
    bool run();
    static bool parsePayload(std::string msg);

private:
    const std::string SERVER_ADDRESS = "tcp://192.168.0.3:1883";
    const std::string CLIENT_ID = "paho_cpp_async_subcribe";
    const std::string USER = "arduino";
    const std::string PW = "foobar";
    const std::vector<std::string> TOPICS = {"homeassistant/binary_sensor/pir_front/state","homeassistant/binary_sensor/pir_back/state"};
    static const int	QOS = 1;
    static const int	N_RETRY_ATTEMPTS = 5;

    // Callbacks for the success or failures of requested actions.
    // This could be used to initiate further action, but here we just log the
    // results to the console.

    class mqtt_action_listener : public virtual mqtt::iaction_listener
    {
        std::string name_;

        void on_failure(const mqtt::token& tok) override;

        void on_success(const mqtt::token& tok) override;

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
        FLURLICHT_MQTT&  parent;

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
        void reconnect();

        // Re-connection failure
        void on_failure(const mqtt::token& tok) override;

        // (Re)connection success
        // Either this or connected() can be used for callbacks.
        void on_success(const mqtt::token& tok) override {}

        // (Re)connection success
        void connected(const std::string& cause) override;

        // Callback for when the connection is lost.
        // This will initiate the attempt to manually reconnect.
        void connection_lost(const std::string& cause) override;

        // Callback for when a message arrives.
        void message_arrived(mqtt::const_message_ptr msg) override;

        void delivery_complete(mqtt::delivery_token_ptr token) override {}

    public:
        mqtt_callback(FLURLICHT_MQTT&  mqtt, mqtt::async_client& cli, mqtt::connect_options& connOpts)
                    : nretry_(0), cli_(cli), connOpts_(connOpts), subListener_("Subscription"), parent(mqtt) {}
        void setTOPIC(const std::string &value);
    };

    std::shared_ptr<FLURLICHT_OCCUPANCY> occupancy_;
    std::shared_ptr<mqtt::async_client> cli_;
    std::shared_ptr<mqtt::connect_options> connOpts_;
    std::shared_ptr<mqtt_callback> cb_;
};


#endif // FLURLICHT_MQTT_H
