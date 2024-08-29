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
   NOTES:                                                                     */
/* -------------------------------------------------------------------------- */

#include "Arduino_ISL28022.h"

ISL28022Class dpm{0.01,Wire1};


/* ____________________________________________________________________setup()*/
void setup() {
   Serial.begin(115200);
   while(!Serial) {

   }
   Serial.println("*** Example on Digital Power Monitor with custom settings");

   ISL28022CfgClass cfg{469.0};

   cfg.setCurrentScale(CurrentScale::Scale_0);
   Serial.println("Scale 0: max measurable current " + String(cfg.getMaxMeasurableCurrent()) + " A");
   cfg.setCurrentScale(CurrentScale::Scale_1);
   Serial.println("Scale 1: max measurable current " + String(cfg.getMaxMeasurableCurrent()) + " A");
   cfg.setCurrentScale(CurrentScale::Scale_2);
   Serial.println("Scale 2: max measurable current " + String(cfg.getMaxMeasurableCurrent()) + " A");
   cfg.setCurrentScale(CurrentScale::Scale_3);
   Serial.println("Scale 3: max measurable current " + String(cfg.getMaxMeasurableCurrent()) + " A");

   cfg.setCurrentScale(CurrentScale::Scale_0);


   dpm.begin(cfg);

}

/* _____________________________________________________________________loop()*/
void loop() {

   bool ovf = false;
   float bus_voltage = dpm.getBusVoltage(ovf);
   Serial.print("Bus Voltage:    ");
   Serial.print(bus_voltage,8);
   Serial.println(" V");

   float shut_voltage = dpm.getShuntVoltage();
   Serial.print("Shunt Voltage: ");
   Serial.print(shut_voltage,8);
   Serial.println(" V");

   float current = dpm.getCurrent();
   Serial.print("Current:       ");
   Serial.print(current,8);
   Serial.println(" A");

   float power = dpm.getCurrent();
   Serial.print("Power:         ");
   Serial.print(power,8);
   Serial.println(" W\n");

   delay(3000);
}




