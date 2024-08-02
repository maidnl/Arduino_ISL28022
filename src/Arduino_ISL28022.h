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

class ISL28022Class;

/* _______________________________________________________CONFIGURATION CLASS */
class ISL28022CfgClass {
   private:
   BusVoltageRange   bus_voltage_range;
   ShuntVoltageRange shunt_voltage_range;
   AdcConf           bus_adc_cfg;
   AdcConf           shunt_adc_cfg;
   MeasureEnabled    enabled_measures;
   MeasureTrigger    measure_trigger;
   uint16_t          shunt_ths;        
   uint16_t          bus_ths;
   float             current_LSB = 0.0;


   uint16_t          encode_config(bool reset);
   uint16_t          calc_calibration(float shunt_res_ohm);

   

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

   

   friend ISL28022Class;


};

/* ______________________________________________________________DEVICE CLASS */
class ISL28022Class {
private:
   TwoWire &_wire;
   uint8_t slave_address;
   bool initialized;
   ISL28022CfgClass cfg{};
   float shunt_res_ohm;


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