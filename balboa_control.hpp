#include "esphome.h"

class MyCustomSensor : public Component, public Sensor {
 public:
  void setup() override {
    // This will be called by App.setup()
  }
  void loop() override {
    // This will be called by App.loop()
  }
};