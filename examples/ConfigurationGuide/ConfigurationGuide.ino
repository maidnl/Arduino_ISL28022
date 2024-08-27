/* -------------------------------------------------------------------------- */
/* FILE NAME:   ConfigurationGuide.ino
   AUTHOR:      Daniele Aimo
   EMAIL:       d.aimo@arduino.cc
   DATE:        20240826
   DESCRIPTION: 
   LICENSE:     Copyright (c) 2024 Arduino SA
                his Source Code Form is subject to the terms fo the Mozilla 
                Public License (MPL), v 2.0. You can obtain a copy of the MPL 
                at http://mozilla.org/MPL/2.0/. 
   NOTES:                                                                     */
/* -------------------------------------------------------------------------- */


/* The purpose of this example is to explain how to configure the ISL28022 
   device
   This example does not use any HW, it just shows some important concepts 
   to be used while choosing the configuration for te ISL28022 device

   To measure the current the ISL28022 device needs an extenal Resistor
   This resistor has to be choose keeping in mind the Full Scale of the 
   current we want to measure

   A detailed description can be found in the ISL28022 datasheet
   In general an HIGH value of Resistance (order of magnitude 1 Kohm)
   can be used to measure low currents (around 100 uA as max value)
   while LOW value of resistance (order of magnitude 0.10 ohm) are used to measure
   HIGH value of max current (around 500 A)

   How to choose the correct resistor for your application is outside the
   scope of this example and won't be explained here (refer to datasheet TABLE 24)

   Once a shunt resistor is choosen the ISL28022 can adjust its gain or PGA
   to determine the full scale (i.e. the maximum measurable current).
   
   In this library the gain are mapped into 4 different Scale (see enumeration
   CurrentScale) from Scale_0 to Scale_3. (see PGA)

   Scale_0 is the "smaller" i.e. is the scale that allow the measure of the
   smaller range of current for the choosen shunt 
   resistor value

   Scale_3 is the "bigger" i.e. is the scale that allow the measure of the bigger 
   range of current for the choosen shunt resistor value


*/

#include "Arduino_ISL28022.h"



/* ____________________________________________________________________setup()*/
void setup() {
   Serial.begin(115200);
   while(!Serial) {

   }
   Serial.println("*** EXAMPLE: configuration guide ");

   /* configuration class -> take the value of the shunt resistor in ohm */
   ISL28022CfgClass cfg{0.01}; // shunt resistor 10 mohm


   /*  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
       SHUNT RESISTOR 0.01 ohm
       +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

   /* 
    *  SCALE 0 
    */
   cfg.setCurrentScale(CurrentScale::Scale_0);

   float resolution = cfg.getResolution();
   float max_current = cfg.getMaxMeasurableCurrent();

   Serial.println("Shunt Resistor: " + String(cfg.getShuntResistor()) + " ohm");
   Serial.println("Scale 0: max measurable current " + String(max_current) + " A");
   Serial.println("Scale 0: resolution " + String(resolution,8) + " A");

   Serial.println();

   /* 
    *  SCALE 1 
    */
   cfg.setCurrentScale(CurrentScale::Scale_1);

   resolution = cfg.getResolution();
   max_current = cfg.getMaxMeasurableCurrent();

   Serial.println("Shunt Resistor: " + String(cfg.getShuntResistor()) + " ohm");
   Serial.println("Scale 1: max measurable current " + String(max_current) + " A");
   Serial.println("Scale 1: resolution " + String(resolution,8) + " A");

   Serial.println();

   /* 
    *  SCALE 2 
    */
   cfg.setCurrentScale(CurrentScale::Scale_2);

   resolution = cfg.getResolution();
   max_current = cfg.getMaxMeasurableCurrent();

   Serial.println("Shunt Resistor: " + String(cfg.getShuntResistor())+ " ohm" );
   Serial.println("Scale 2: max measurable current " + String(max_current) + " A");
   Serial.println("Scale 2: resolution " + String(resolution,8) + " A");

   Serial.println();

   /* 
    *  SCALE 3 
    */
   cfg.setCurrentScale(CurrentScale::Scale_3);

   resolution = cfg.getResolution();
   max_current = cfg.getMaxMeasurableCurrent();

   Serial.println("Shunt Resistor: " + String(cfg.getShuntResistor()) + " ohm");
   Serial.println("Scale 3: max measurable current " + String(max_current) + " A");
   Serial.println("Scale 3: resolution " + String(resolution,8) + " A");

   Serial.println("\n------------------------------------------------------");

   /*  +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
       SHUNT RESISTOR 0.270 ohm
       +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

   cfg.setShuntResistor(0.270);

   cfg.setCurrentScale(CurrentScale::Scale_0);

   resolution = cfg.getResolution();
   max_current = cfg.getMaxMeasurableCurrent();

   Serial.println("Shunt Resistor: " + String(cfg.getShuntResistor()) + " ohm");
   Serial.println("Scale 0: max measurable current " + String(max_current) + " A");
   Serial.println("Scale 0: resolution " + String(resolution,8) + " A");

   Serial.println();

   /* 
    *  SCALE 1 
    */
   cfg.setCurrentScale(CurrentScale::Scale_1);

   resolution = cfg.getResolution();
   max_current = cfg.getMaxMeasurableCurrent();

   Serial.println("Shunt Resistor: " + String(cfg.getShuntResistor()) + " ohm");
   Serial.println("Scale 1: max measurable current " + String(max_current) + " A");
   Serial.println("Scale 1: resolution " + String(resolution,8) + " A");

   Serial.println();

   /* 
    *  SCALE 2 
    */
   cfg.setCurrentScale(CurrentScale::Scale_2);

   resolution = cfg.getResolution();
   max_current = cfg.getMaxMeasurableCurrent();

   Serial.println("Shunt Resistor: " + String(cfg.getShuntResistor())+ " ohm" );
   Serial.println("Scale 2: max measurable current " + String(max_current) + " A");
   Serial.println("Scale 2: resolution " + String(resolution,8) + " A");

   Serial.println();

   /* 
    *  SCALE 3 
    */
   cfg.setCurrentScale(CurrentScale::Scale_3);

   resolution = cfg.getResolution();
   max_current = cfg.getMaxMeasurableCurrent();

   Serial.println("Shunt Resistor: " + String(cfg.getShuntResistor()) + " ohm");
   Serial.println("Scale 3: max measurable current " + String(max_current) + " A");
   Serial.println("Scale 3: resolution " + String(resolution,8) + " A");


}

/* _____________________________________________________________________loop()*/
void loop() {

   
}


