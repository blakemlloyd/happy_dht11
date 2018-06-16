#ifndef happy_dht11_h
#define happy_dht11_h

#include "Arduino.h"
#include "DHT.h"
#include <PubSubClient.h>

class happy_dht11
{
    public:
        happy_dht11(int pin, PubSubClient client);
        void setId(char* id);
        bool checkTemp();
        bool checkHumid();
    private:
        int _pin;
        long _lastTempMsg;
        long _lastHumidMsg;
        float _temp;
        float _humid;
        PubSubClient _client;
        char *tempConfigTopic;
        char *humidConfigTopic;
        char *tempStateTopic;
        char *humidStateTopic;
        char *tempConfig;
        char *humidConfig;
        DHT *_dht;
};

#endif