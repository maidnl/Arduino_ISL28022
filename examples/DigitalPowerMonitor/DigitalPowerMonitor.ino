/* -------------------------------------------------------------------------- */
/* FILE NAME:   DigitalPowerMonitor.ino
   AUTHOR:      Daniele Aimo
   EMAIL:       d.aimo@arduino.cc
   DATE:        20240730
   DESCRIPTION: 
   LICENSE:     Copyright (c) 2024 Arduino SA
                his Source Code Form is subject to the terms fo the Mozilla 
                Public License (MPL), v 2.0. You can obtain a copy of the MPL 
                at http://mozilla.org/MPL/2.0/. 
   NOTES: modified by Silvio Navaretti                                        */
/* -------------------------------------------------------------------------- */

#include "Arduino_ISL28022.h"

//Sense resisto on board 0.1 ohm
//To use it with UNO R4 QWIIC connector, Wire1 is used
ISL28022Class dpm{0.1, Wire1};

void setup() {
  Serial.begin(115200);

  //Do not start until serial monitor is opened
  while (!Serial) {}
  Serial.println("Starting Example on Digital Power Monitor");

  //Board inizialization
  dpm.begin();
}

void loop() {
  bool ovf = false;
  float bus_voltage = dpm.getBusVoltage(ovf);
  Serial.print("Bus Voltage: ");
  Serial.print(bus_voltage, 3);
  Serial.print(" V ");

  //Shunt voltage LSB = 10uV
  float shut_voltage = dpm.getShuntVoltage();
  Serial.print(" Shunt Voltage: ");
  Serial.print(shut_voltage*1000, 3);
  Serial.print(" mV ");

  //Current is shunt voltage / sense resistor
  float current = dpm.getCurrent();
  Serial.print(" Current: ");
  Serial.print(current*1000, 3);
  Serial.print(" mA ");

  //Power is bus voltage * current
  float power = dpm.getCurrent();
  Serial.print("Power: ");
  Serial.print(power, 8);
  Serial.print(" W\n");

  delay(100);
}
