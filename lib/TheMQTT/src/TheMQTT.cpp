#include "TheMQTT.hpp"

TheMQTT::TheMQTT() : mqtt(espClient) {}

void TheMQTT::setup()
{
    mqttSetupOk = false;
}

void TheMQTT::loop()
{
    if (!mqttSetupOk)
        return;
    if (!mqtt.connected())
        connect();
    mqtt.loop();
}

void TheMQTT::doInit(String uid, String ip, String user, String password)
{
    mqttUid = uid;
    mqttIpAddress = ip;
    mqttUser = user;
    mqttPassword = password;
    Serial.println("MQTT: server=" + mqttIpAddress + ", port=" + String(mqttPort));
    mqtt.setServer(mqttIpAddress.c_str(), mqttPort);
    mqtt.setCallback(theCallback);
    mqttSetupOk = true;
}

bool TheMQTT::isValid()
{
    return mqttSetupOk;
}

void TheMQTT::connect()
{
    if (mqtt.connected())
        return;
    if ((millis() - mqttLastTry) < MQTT_DELAY_RETRY)
    {
        static uint16_t count = 0;
        count++;
        if (count > 30 * 1000)
        {
            count = 0;
            Serial.print(".");
        }
        return;
    }
    mqttLastTry = millis();
    Serial.println("MQTT: attempting connection");
    if (mqtt.connect(mqttUid.c_str(), mqttUser.c_str(), mqttPassword.c_str()))
    {
        Serial.println("MQTT: connected!");
        if (callbackConnected)
            callbackConnected();
    }
    else
    {
        Serial.print("MQTT: failed, rc=");
        Serial.print(mqtt.state());
        Serial.println(". Try again in 5 seconds");
    }
}

void TheMQTT::publish(String topic, String data)
{
    if (!mqttSetupOk)
        return;
    if (!mqtt.connected())
        return;
    Serial.println("MQTT=> " + topic + " " + data + "(" + data.length() + ")");
    mqtt.publish(topic.c_str(), data.c_str());
}

void TheMQTT::eventConnected(THE_MQTT_CONNECTED callback)
{
    callbackConnected = callback;
    Serial.println("TheMQTT callback connected set");
}

void TheMQTT::eventReceive(THE_MQTT_EVENT_RECEIVE callback)
{
    theCallback = callback;
    Serial.println("TheMQTT callback receive set");
}