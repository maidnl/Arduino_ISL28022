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
   Serial.println("Starting Example on Digital Power Monitor");

   dpm.begin();

   Serial.println("*** READING all register (for testing purposes)...");

   Serial.print("Shunt voltage:     ");
   Serial.println(dpm.read(ADD_CONFIGURATION_REG),HEX);

   Serial.print("Bus voltage:       ");
   Serial.println(dpm.read(ADD_SHUNT_VOLTAGE_REG),HEX);

   Serial.print("Power:             ");
   Serial.println(dpm.read(ADD_POWER_REG),HEX);

   Serial.print("Current:           ");
   Serial.println(dpm.read(ADD_CURRENT_REG),HEX);

   Serial.print("Calibration:       ");
   Serial.println(dpm.read(ADD_CALIBRATION_REG),HEX);

   Serial.print("Shunt thresholds:  ");
   Serial.println(dpm.read(ADD_SHUNT_VOLTAGE_TH_REG),HEX);

   Serial.print("Bus thresholds:    ");
   Serial.println(dpm.read(ADD_BUS_VOLTAGE_TH_REG),HEX);

   Serial.print("Threshols INT:     ");
   Serial.println(dpm.read(ADD_DCS_INTERRUPT_STATUS_REG),HEX);

   Serial.print("AUX control:       ");
   Serial.println(dpm.read(ADD_AUX_CONTROL_REG),HEX);

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

   delay(5000);
}




