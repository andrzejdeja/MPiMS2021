#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include "L3G4200D.hpp"
#include "GyroscopeManager.hpp"
#include "TiltCalculator.hpp"
#include "ServoManager.hpp"


TiltCalculator tiltCalculator(-0.000003);


void setup() {
  GyroscopeManager::getInstance().setup();
  ServoManager::getInstance().setup(3);
}

void loop() {
  ServoManager::getInstance().moveServos(tiltCalculator.CalcCounter(GyroscopeManager::getInstance().readGyroRaw()));  
}
