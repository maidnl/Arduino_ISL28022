#ifndef ARDUINO_ISL28022_H
#define ARDUINO_ISL28022_H

#include <Arduino.h>
#include <Wire.h>

#include "ISL28022.h"

#define DEFAULT_SLAVE_ADDRESS 0x40

/* __________________________________________________________________________ */
enum BusVoltageRange {
   RNG_16V,
   RNG_32V,
   RNG_60V
};

/* __________________________________________________________________________ */
enum ShuntVoltageRange {
   RNG_40mv,
   RNG_80mV,
   RNG_160mv,
   RNG_320mv
};

/* __________________________________________________________________________ */
enum AdcConf {
   CFG_12bit,
   CFG_13bit,
   CFG_14bit,
   CFG_15bit,
   CFG_15bit_with_1average, //result equal to 15bit (define for completeness)
   CFG_15bit_with_2average,
   CFG_15bit_with_4average,
   CFG_15bit_with_8average,
   CFG_15bit_with_16average,
   CFG_15bit_with_32average,
   CFG_15bit_with_64average,
   CFG_15bit_with_128average
};

/* __________________________________________________________________________ */
enum MeasureEnabled  {
   SHUNT,
   VOLTAGE,
   BOTH_SHUNT_AND_VOLTAGE
};

/* __________________________________________________________________________ */
enum MeasureTrigger {
   ON_DEMAND,
   CONTINUOSLY
};

/* _______________________________________________________CONFIGURATION CLASS */
class ISL28022CfgClass {
   private:
   BusVoltageRange   bus_voltage_range;
   ShuntVoltageRange shunt_voltage_range;
   AdcConf           bus_adc_cfg;
   AdcConf           shunt_adc_cfg;
   MeasureEnabled     enabled_measures;
   MeasureTrigger    measure_trigger;
   uint16_t          shunt_ths;        
   uint16_t          bus_ths;

   public:
   ISL28022CfgClass() {
      bus_voltage_range = BusVoltageRange::RNG_60V;
      shunt_voltage_range = ShuntVoltageRange::RNG_320mv;
      bus_adc_cfg = AdcConf::CFG_15bit;
      shunt_adc_cfg = AdcConf::CFG_15bit;
      enabled_measures = MeasureEnabled::BOTH_SHUNT_AND_VOLTAGE;
      measure_trigger = MeasureTrigger::CONTINUOSLY;
   }
   ~ISL28022CfgClass() {}
   void setBusVoltageRange(BusVoltageRange vr) { bus_voltage_range = vr; }
   void setShuntVoltageRange(ShuntVoltageRange vr) { shunt_voltage_range = vr; }
   void setBusAdcCfg(AdcConf cfg) { bus_adc_cfg = cfg; }
   void setMeasurement(MeasureEnabled me, MeasureTrigger mt) {
      enabled_measures = me;
      measure_trigger = mt;
   }

};

/* ______________________________________________________________DEVICE CLASS */
class ISL28022Class {
private:
   TwoWire &_wire;
   uint8_t slave_address;
   bool initialized;

public:
   /* default Wire, default address 0x40 (from altium TBV) */
   ISL28022Class();
   /* default Wire, default address = a */
   ISL28022Class(uint8_t a);
   /* Wire = w, default address 0x40 (from altium TBV) */
   ISL28022Class(TwoWire &w);
   /* Wire = w, default address = a */
   ISL28022Class(TwoWire &w, uint8_t a);

   ~ISL28022Class();

   bool begin();
   bool begin(ISL28022CfgClass &cfg);

   float getBusVoltage();
   float getShuntVoltage();
   float getCurrent();
   float getPower();




};



#endif