#include "esphome.h"
#include "Adafruit_TSL2591.h"

class Tsl2591 : public PollingComponent, public Sensor {
 public:
  // constructor
  Tsl2591() : PollingComponent(15000) {}
  Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591);

  void setup() override {
    if (!tsl.begin()) 
    {
      ESP_LOGD("ERROR","Could not find a TSL2591 Sensor. Did you configure I2C?");
    } 
    tsl.setGain(TSL2591_GAIN_LOW);      //We use the lowest possible gain.
    tsl.setTiming(TSL2591_INTEGRATIONTIME_600MS); //We use the longest possible Integration Time for accurate Results.
    //For more details on Gain and Integration Time see the Adafruit Repository for the TSL2591 Sensor
  }
  void update() override {   
    uint16_t x = tsl.getLuminosity(TSL2591_VISIBLE);  //We only measure the visible light
    publish_state(x);
  }
};