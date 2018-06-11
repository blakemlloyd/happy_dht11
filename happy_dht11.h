#ifndef happy_button_h
#define happy_button_h

#include "Arduino.h"
#include "DHT.h"

class happy_dht11
{
    public:
        happy_dht11(int pin);
        bool isTempUpdated();
        bool isHumidUpdated();
        float getTemp();
        float getHumid();
    private:
        int _pin;
        long _lastTempMsg;
        long _lastHumidMsg;
        float _temp;
        float _humid;
}

#endif