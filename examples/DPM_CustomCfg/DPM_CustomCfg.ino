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

   /* this make a new configuration with a different shunt resistor value */
   ISL28022CfgClass cfg{469.0};
   /* this change the current range 
    * scale 0 -> 40mv 
    * scale 1 -> 80mv
    * scale 2 -> 160mv
    * scale 3 -> 320mv */
   cfg.setCurrentScale(CurrentScale::Scale_0);
   
   /* change here other configuration as you wish */

   /* then call begin with the new configuration set */
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




