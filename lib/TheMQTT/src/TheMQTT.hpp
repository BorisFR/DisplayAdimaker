#ifndef THE_MQTT_HPP
#define THE_MQTT_HPP

#include <WiFiClient.h>
#include <PubSubClient.h>

#define MQTT_DELAY_RETRY 5 * 1000

#define THE_MQTT_CONNECTED std::function<void()>
#define THE_MQTT_EVENT_RECEIVE std::function<void(char *topic, byte *payload, unsigned int length)>

class TheMQTT
{
public:
    TheMQTT();
    void setup();
    void loop();
    void doInit(String uid, String ip, String user, String password);
    bool isValid();
    void eventConnected(THE_MQTT_CONNECTED callback);
    void eventReceive(THE_MQTT_EVENT_RECEIVE callback);
    void publish(String topic, String data);

private:
    WiFiClient espClient;
    PubSubClient mqtt;
    bool mqttSetupOk = false;
    String mqttUid;
    String mqttIpAddress;
    String mqttUser;
    String mqttPassword;
    uint16_t mqttPort = 1883;
    unsigned long mqttLastTry = 0;
    THE_MQTT_EVENT_RECEIVE theCallback;
    THE_MQTT_CONNECTED callbackConnected;
    void connect();
    // void receivedData(char *topic, byte *payload, unsigned int length);
};

#endif