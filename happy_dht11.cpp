#include "Arduino.h"
#include "happy_dht11.h"

float diff = 1.0;

happy_dht11::happy_dht11(int pin, PubSubClient client)
{
    _pin = pin;
    _client = client;
    DHT dht(pin, DHT11);
    _dht = &dht;
    _dht->begin();
}

void happy_dht11::setId(char* id)
{
    tempConfigTopic = (char*)malloc(strlen(id) + 34 + 1);
    snprintf(tempConfigTopic, strlen(id) + 34, "homeassistant/sensor/%s-temp/config", id);

    humidConfigTopic = (char*)malloc(strlen(id) + 35 + 1);
    snprintf(humidConfigTopic, strlen(id) + 35, "homeassistant/sensor/%s-humid/config", id);
    
    tempConfig = (char*)malloc(strlen(id) + 48 + 1);
    snprintf(tempConfig, strlen(id) + 48, "{\"name\": \"%s-temp\", \"unit_of_measurement\": \"°C\"}", id);

    humidConfig = (char*)malloc(strlen(id) + 47 + 1);
    snprintf(humidConfig, strlen(id) + 47, "{\"name\": \"%s-humid\", \"unit_of_measurement\": \"%%\"}", id);
    
    tempStateTopic = (char*)malloc(strlen(id) + 33 + 1);
    snprintf(tempStateTopic, strlen(id) + 33, "homeassistant/sensor/%s-temp/state", id);

    humidStateTopic = (char*)malloc(strlen(id) + 34 + 1);
    snprintf(humidStateTopic, strlen(id) + 34, "homeassistant/sensor/%s-humid/state", id);
    
    _client.publish(tempConfigTopic, tempConfig, true);
    _client.publish(humidConfigTopic, humidConfig, true);
}

bool checkBound(float newValue, float prevValue, float maxDiff) {
    return !isnan(newValue) &&
         (newValue < prevValue - maxDiff || newValue > prevValue + maxDiff);
}

bool happy_dht11::checkTemp()
{
    long now = millis();
    if(now - _lastTempMsg > 1000)
    {
        _lastTempMsg = now;
        float newTemp = _dht->readTemperature();

        if(checkBound(newTemp, _temp, diff))
        {
            _temp = newTemp;
            _client.publish(tempStateTopic, String(_temp).c_str(), true);
            return true;
        }
    }
    return false;
}

bool happy_dht11::checkHumid()
{
    long now = millis();
    if(now - _lastHumidMsg > 1000)
    {
        _lastHumidMsg = now;
        float newHumid = _dht->readHumidity();

        if(checkBound(newHumid, _humid, diff))
        {
            _humid = newHumid;
            _client.publish(humidStateTopic, String(_humid).c_str(), true);
            return true;
        }
    }
    return false;
}