#include <ArduinoLowPower.h>

// NOTE TO MY REVIEWER: PLEASE READ ME

// The way to save or optimize on power is to run the microcontroller in low power mode 
// This usually includes two tiers - Light sleep and deep sleep
// The normal active mode consumes about 160mA of current
// The light sleep mode consumes about 2-10mA of current
// The deep sleep mode mode consumes 10-100µA of current
// How it works is that the microcontroller turns off a variety of internal modules and keeps
// only the most vital modules on. Usually in the setup a trigger pin is set 
// so that any change to that trigger pin can wake the board up

// In this example I'm showing how to use the low power module from Arduino itself.
// The board sleeps for 5 seconds and when you use the deepSleep option
// Then the board deepSleeps for 5 seconds. You can track the sleep time with the built in led on the board.

// I have implemented the deepSleep version in the other files so that 
// The board saves power if connected to a battery source.

// UPDATE
// I have just commented the deepSleep in the other files out but when testing you can
// turn it back on.


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  LowPower.sleep(5000);
  // LowPower.deepSleep(5000);
}