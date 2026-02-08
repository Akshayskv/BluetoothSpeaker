#include <Arduino.h>
#include "AudioTools.h"
#include "BluetoothA2DPSink.h"

I2SStream i2s;
BluetoothA2DPSink sink(i2s);

void setup() {
  sink.start("my_music");
}

void loop() {
  
}
