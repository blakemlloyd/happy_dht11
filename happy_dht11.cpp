#include "Arduino.h"
#include "happy_button.h"

class happy_dht11
{
    float diff = 1.0;

    happy_button::happy_dht11(int pin)
    {
        _pin = pin;
        DHT dht(pin, DHT11);
        dht.begin();
    }

    bool checkBound(float newValue, float prevValue, float maxDiff) {
        return !isnan(newValue) &&
             (newValue < prevValue - maxDiff || newValue > prevValue + maxDiff);
    }

    bool happy_button::isTempUpdated()
    {
        long now = millis();
        if(now - _lastTempMsg > 1000)
        {
            _lastTempMsg = now;
            float newTemp = dht.readTemperature();

            if(checkBound(newTemp, _temp, diff))
            {
                _temp = newTemp;
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    bool happy_button::isHumidUpdated()
    {
        long now = millis();
        if(now - _lastHumidMsg > 1000)
        {
            _lastHumidMsg = now;
            float newHumid = dht.readHumidity();

            if(checkBound(newHumid, _humid, diff))
            {
                _humid = newHumid;
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}