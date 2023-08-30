#pragma once
#include "esphome.h"
#include "balboa_messages.hpp"

namespace balboa
{

class BalboaSpa : public Component {
 public:
  void setup() override {
    // This will be called by App.setup()
    Message<ConfigRequest> message;

    ConfigRequest::SetPayload(true, message._data);

  }
  void loop() override {
    // This will be called by App.loop()
  }
};
};