#ifndef ARDUINO_ISL28022_H
#define ARDUINO_ISL28022_H

#include <Arduino.h>
#include <Wire.h>

#include "ISL28022.h"

#define DEFAULT_SLAVE_ADDRESS 0x40
#define TX_BUFFER_DIM 3
#define RX_BUFFER_DIM 2
#define READ_TIMEOUT 50

/* __________________________________________________________________________ */
enum class BusVoltageRange {
   RNG_16V,
   RNG_32V,
   RNG_60V
};

/* __________________________________________________________________________ */
enum class ShuntVoltageRange {
   RNG_40mv,
   RNG_80mV,
   RNG_160mv,
   RNG_320mv
};

/* __________________________________________________________________________ */
enum class AdcConf {
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
enum class MeasureEnabled  {
   SHUNT,
   VOLTAGE,
   BOTH_SHUNT_AND_VOLTAGE
};

/* __________________________________________________________________________ */
enum class MeasureTrigger {
   ON_DEMAND,
   CONTINUOSLY
};

/* __________________________________________________________________________ */
enum class CurrentScale {
   Scale_0,
   Scale_1,
   Scale_2,
   Scale_3
};

class ISL28022Class;

/* _______________________________________________________CONFIGURATION CLASS */
class ISL28022CfgClass {
   private:

   BusVoltageRange   bus_voltage_range = BusVoltageRange::RNG_60V;;
   ShuntVoltageRange shunt_voltage_range = ShuntVoltageRange::RNG_320mv;
   AdcConf           bus_adc_cfg = AdcConf::CFG_15bit;
   AdcConf           shunt_adc_cfg = AdcConf::CFG_15bit;;
   MeasureEnabled    enabled_measures = MeasureEnabled::BOTH_SHUNT_AND_VOLTAGE;
   MeasureTrigger    measure_trigger = MeasureTrigger::CONTINUOSLY;
   uint16_t          shunt_ths;        
   uint16_t          bus_ths;
   float             current_LSB = 0.0;
   
   CurrentScale      current_scale = CurrentScale::Scale_3;
   float             r_shunt_value_ohm;

   uint16_t          encode_config(bool reset);
   uint16_t          calc_calibration(float shunt_res_ohm);

   

   public:
   ISL28022CfgClass(float shunt_ohm) : r_shunt_value_ohm(shunt_ohm){ }
   ~ISL28022CfgClass() {}
   void setBusVoltageRange(BusVoltageRange vr) { bus_voltage_range = vr; }
   void setShuntVoltageRange(ShuntVoltageRange vr) { 
      shunt_voltage_range = vr; 
      if(ShuntVoltageRange::RNG_40mv == vr) {
         current_scale = CurrentScale::Scale_0;
      } else if(ShuntVoltageRange::RNG_80mv == vr) {
         current_scale = CurrentScale::Scale_1;
      } else if(ShuntVoltageRange::RNG_160mv == vr) {
         current_scale = CurrentScale::Scale_2;
      } else if(ShuntVoltageRange::RNG_320mv == vr) {
         current_scale = CurrentScale::Scale_3;
      } 
   }
   

   void setBusAdcCfg(AdcConf cfg) { bus_adc_cfg = cfg; }
   void setMeasurement(MeasureEnabled me, MeasureTrigger mt) {
      enabled_measures = me;
      measure_trigger = mt;
   }

   float getMaxMeasurableCurrent() {
      if(r_shunt_value_ohm <= 0) {
         return 0.0;
      }

      if (current_scale == CurrentScale::Scale_3) {
         return 0.320 / r_shunt_value_ohm;
      } else if (current_scale == CurrentScale::Scale_2) {
         return 0.160 / r_shunt_value_ohm;
      } else if (current_scale == CurrentScale::Scale_1) {
         return 0.080 / r_shunt_value_ohm;
      } else if (current_scale == CurrentScale::Scale_0) {
         return 0.040 / r_shunt_value_ohm;
      } 
      return 0.0;
   }

   float getResolution() {
      if(r_shunt_value_ohm <= 0) {
         return 0.0;
      }
      return 0.000010 / r_shunt_value_ohm;
   }

   float getShuntResistor() {
      return r_shunt_value_ohm;
   }

   void setShuntResistor(float o) {
      r_shunt_value_ohm = o;
   }

   void setCurrentScale(CurrentScale cs) {
      current_scale = cs;
      if(cs == CurrentScale::Scale_0) {
         shunt_voltage_range = ShuntVoltageRange::RNG_40mv;
      } else if(cs == CurrentScale::Scale_1) {
         shunt_voltage_range = ShuntVoltageRange::RNG_80mv;
      } else if(cs == CurrentScale::Scale_2) {
         shunt_voltage_range = ShuntVoltageRange::RNG_160mv;
      } else if(cs == CurrentScale::Scale_3) {
         shunt_voltage_range = ShuntVoltageRange::RNG_320mv;
      } 
   }

   friend ISL28022Class;


};

/* ______________________________________________________________DEVICE CLASS */
class ISL28022Class {
private:
   TwoWire &_wire;
   uint8_t slave_address;
   bool initialized;
   float shunt_res_ohm;
   ISL28022CfgClass cfg;
   
   uint8_t tx_buffer[TX_BUFFER_DIM];
   uint8_t rx_buffer[RX_BUFFER_DIM];

   void send(int add, uint8_t n, uint8_t r);
   bool receive(uint8_t n, uint16_t timeout);
   void write(uint8_t reg_add, uint16_t value);
   
   uint16_t demand_conversion(); // return bus voltage register value

public:
   /* default Wire, default address 0x40 (from altium TBV) */
   ISL28022Class(float _shunt_res_ohm);
   /* default Wire, default address = a */
   ISL28022Class(float _shunt_res_ohm, uint8_t a);
   /* Wire = w, default address 0x40 (from altium TBV) */
   ISL28022Class(float _shunt_res_ohm, TwoWire &w);
   /* Wire = w, default address = a */
   ISL28022Class(float _shunt_res_ohm, TwoWire &w, uint8_t a);

   ~ISL28022Class();

   operator bool();

   bool begin();
   bool begin(ISL28022CfgClass &_cfg);

   float getBusVoltage(bool &overflow);
   float getShuntVoltage();
   float getCurrent();
   float getPower();
   
   void setShuntVoltageThreshold(float low, float high);
   void setBusThresholds(float low, float high);
   bool shuntUnderThVoltage();
   bool shuntOverThVoltage();
   bool busUnderThVoltage();
   bool busOverThVoltage();

   void forceEXTCLK_INTpinToLow();
   void useEXTCLK_INTpinForThreshold();

   /* the divider must be provided in a way that 
                       (frequ_external)
      freq_internal = -------------------
                        (div + 1) * 2
   */
   void useExternalClock(uint8_t div);

   uint16_t read(uint8_t reg_add);

};



#endif