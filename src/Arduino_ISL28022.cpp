#include "Arduino_ISL28022.h"

/* -------------------------------------------------------------------------- */
/*                         "PRIVATE" static functions                         */
/* -------------------------------------------------------------------------- */

/* __________________________________________________________________________ */
static uint16_t int2two(int32_t val, uint8_t bits) {
   uint16_t max_value = (1 << (bits)) - 1;
   uint16_t rv = val < 0 ? -val : val;
   rv = ~rv;
   rv += 1;
   rv &= max_value;
   return rv;
}

/* __________________________________________________________________________ */
static int32_t two2int(uint32_t val, uint8_t bits) {
    uint32_t rv = 0;
    if(val & (1 << (bits-1))) {
        rv = -(1 << bits) + (val & ((1 << bits ) -1));
    }
    else {
        rv = (int32_t)val;
    }
    return rv;
}

/* -------------------------------------------------------------------------- */
/*                 ISL28022CfgClass implementation                            */
/* -------------------------------------------------------------------------- */

#define DEBUG_CFG

/* __________________________________________________________________________ */
uint16_t ISL28022CfgClass::encode_config(bool reset) {
   uint16_t rv = 0;

   #ifdef DEBUG_CFG
   Serial.println("config initial value = " + String(rv));
   #endif
   
   if(reset) {
      SET_RESET_AND_CALIBRATE(rv);
      #ifdef DEBUG_CFG
      Serial.println("RESET config value = " + String(rv));
      #endif  
   }

   if(bus_voltage_range == BusVoltageRange::RNG_16V) {
      BUS_VOLTAGE_RANGE_16V(rv);
      #ifdef DEBUG_CFG
      Serial.println("BUS voltage range 16V config value = " + String(rv));
      #endif
   } else if (bus_voltage_range == BusVoltageRange::RNG_32V) {
      BUS_VOLTAGE_RANGE_32V(rv);
      #ifdef DEBUG_CFG
      Serial.println("BUS voltage range 32V config value = " + String(rv));
      #endif
   } else {
      BUS_VOLTAGE_RANGE_60V(rv);
      #ifdef DEBUG_CFG
      Serial.println("BUS voltage range 60V config value = " + String(rv));
      #endif
   }

   if(shunt_voltage_range == ShuntVoltageRange::RNG_40mv) {
      SHUNT_VOLTAGE_RANGE_40mv(rv);
      #ifdef DEBUG_CFG
      Serial.println("SHUNT voltage range 40mV config value = " + String(rv));
      #endif
      
   } else if (shunt_voltage_range == ShuntVoltageRange::RNG_80mv) {
      SHUNT_VOLTAGE_RANGE_80mv(rv);
      #ifdef DEBUG_CFG
      Serial.println("SHUNT voltage range 80mV config value = " + String(rv));
      #endif
   } else if (shunt_voltage_range == ShuntVoltageRange::RNG_160mv) {
      SHUNT_VOLTAGE_RANGE_160mv(rv);
      #ifdef DEBUG_CFG
      Serial.println("SHUNT voltage range 160mV config value = " + String(rv));
      #endif
   } else {
      SHUNT_VOLTAGE_RANGE_320mv(rv);
      #ifdef DEBUG_CFG
      Serial.println("SHUNT voltage range 320mV config value = " + String(rv));
      #endif
      
   }

   if(bus_adc_cfg == AdcConf::CFG_12bit) {
      BUS_ADC_CFG_12b(rv);
      #ifdef DEBUG_CFG
      Serial.println("BUS adc 12 config value = " + String(rv));
      #endif
   } else if (bus_adc_cfg == AdcConf::CFG_13bit) {
      BUS_ADC_CFG_13b(rv);
      #ifdef DEBUG_CFG
      Serial.println("BUS adc 13 config value = " + String(rv));
      #endif
   } else if (bus_adc_cfg == AdcConf::CFG_14bit) {
      BUS_ADC_CFG_14b(rv);
      #ifdef DEBUG_CFG
      Serial.println("BUS adc 14 config value = " + String(rv));
      #endif
   } else if (bus_adc_cfg == AdcConf::CFG_15bit) {
      BUS_ADC_CFG_15b(rv);
      #ifdef DEBUG_CFG
      Serial.println("BUS adc 15 config value = " + String(rv));
      #endif
   } else if (bus_adc_cfg == AdcConf::CFG_15bit_with_1average) {
      BUS_ADC_CFG_15b_AV1(rv);
      #ifdef DEBUG_CFG
      Serial.println("BUS adc 15-1 config value = " + String(rv));
      #endif
   } else if (bus_adc_cfg == AdcConf::CFG_15bit_with_2average) {
      BUS_ADC_CFG_15b_AV2(rv);
      #ifdef DEBUG_CFG
      Serial.println("BUS adc 15-2 config value = " + String(rv));
      #endif 
   } else if (bus_adc_cfg == AdcConf::CFG_15bit_with_4average) {
      BUS_ADC_CFG_15b_AV4(rv);
      #ifdef DEBUG_CFG
      Serial.println("BUS adc 15-4 config value = " + String(rv));
      #endif 
   } else if (bus_adc_cfg == AdcConf::CFG_15bit_with_8average) {
      BUS_ADC_CFG_15b_AV8(rv);
      #ifdef DEBUG_CFG
      Serial.println("BUS adc 15-8 config value = " + String(rv));
      #endif
   } else if (bus_adc_cfg == AdcConf::CFG_15bit_with_16average) {
      BUS_ADC_CFG_15b_AV16(rv);
       #ifdef DEBUG_CFG
      Serial.println("BUS adc 15-16 config value = " + String(rv));
      #endif
   } else if (bus_adc_cfg == AdcConf::CFG_15bit_with_32average) {
      BUS_ADC_CFG_15b_AV32(rv);
      #ifdef DEBUG_CFG
      Serial.println("BUS adc 15-32 config value = " + String(rv));
      #endif
      
   } else if (bus_adc_cfg == AdcConf::CFG_15bit_with_64average) {
      BUS_ADC_CFG_15b_AV64(rv);
      #ifdef DEBUG_CFG
      Serial.println("BUS adc 15-64 config value = " + String(rv));
      #endif
      
   } else if (bus_adc_cfg == AdcConf::CFG_15bit_with_128average) {
      BUS_ADC_CFG_15b_AV128(rv);
      #ifdef DEBUG_CFG
      Serial.println("BUS adc 15-128 config value = " + String(rv));
      #endif
   } else {
      BUS_ADC_CFG_15b(rv);
      #ifdef DEBUG_CFG
      Serial.println("BUS adc 15-1-default config value = " + String(rv));
      #endif
      
   }

   if(shunt_adc_cfg == AdcConf::CFG_12bit) {
      SHUNT_ADC_CFG_12b(rv);
      #ifdef DEBUG_CFG
      Serial.println("SHUNT adc 12 config value = " + String(rv));
      #endif
      
   } else if (shunt_adc_cfg == AdcConf::CFG_13bit) {
      SHUNT_ADC_CFG_13b(rv);
      #ifdef DEBUG_CFG
      Serial.println("SHUNT adc 13 config value = " + String(rv));
      #endif
      
   } else if (shunt_adc_cfg == AdcConf::CFG_14bit) {
      SHUNT_ADC_CFG_14b(rv);
      #ifdef DEBUG_CFG
      Serial.println("SHUNT adc 14 config value = " + String(rv));
      #endif
      
   } else if (shunt_adc_cfg == AdcConf::CFG_15bit) {
       SHUNT_ADC_CFG_15b(rv);
      #ifdef DEBUG_CFG
      Serial.println("SHUNT adc 15 config value = " + String(rv));
      #endif
     
   } else if (shunt_adc_cfg == AdcConf::CFG_15bit_with_1average) {
      SHUNT_ADC_CFG_15b_AV1(rv);
      #ifdef DEBUG_CFG
      Serial.println("SHUNT adc 15-1 config value = " + String(rv));
      #endif
      
   } else if (shunt_adc_cfg == AdcConf::CFG_15bit_with_2average) {
      SHUNT_ADC_CFG_15b_AV2(rv);
      #ifdef DEBUG_CFG
      Serial.println("SHUNT adc 15-2 config value = " + String(rv));
      #endif
      
   } else if (shunt_adc_cfg == AdcConf::CFG_15bit_with_4average) {
      SHUNT_ADC_CFG_15b_AV4(rv);
      #ifdef DEBUG_CFG
      Serial.println("SHUNT adc 15-4 config value = " + String(rv));
      #endif
      
   } else if (shunt_adc_cfg == AdcConf::CFG_15bit_with_8average) {
      SHUNT_ADC_CFG_15b_AV8(rv);
      #ifdef DEBUG_CFG
      Serial.println("SHUNT adc 15-8 config value = " + String(rv));
      #endif
      
   } else if (shunt_adc_cfg == AdcConf::CFG_15bit_with_16average) {
      SHUNT_ADC_CFG_15b_AV16(rv);
      #ifdef DEBUG_CFG
      Serial.println("SHUNT adc 15-16 config value = " + String(rv));
      #endif
      
   } else if (shunt_adc_cfg == AdcConf::CFG_15bit_with_32average) {
      SHUNT_ADC_CFG_15b_AV32(rv);
      #ifdef DEBUG_CFG
      Serial.println("SHUNT adc 15-32 config value = " + String(rv));
      #endif
      
   } else if (shunt_adc_cfg == AdcConf::CFG_15bit_with_64average) {
      SHUNT_ADC_CFG_15b_AV64(rv);
      #ifdef DEBUG_CFG
      Serial.println("SHUNT adc 15-64 config value = " + String(rv));
      #endif
      
   } else if (shunt_adc_cfg == AdcConf::CFG_15bit_with_128average) {
      SHUNT_ADC_CFG_15b_AV128(rv);
      #ifdef DEBUG_CFG
      Serial.println("SHUNT adc 15-128 config value = " + String(rv));
      #endif
      
   } else {
      SHUNT_ADC_CFG_15b(rv);
      #ifdef DEBUG_CFG
      Serial.println("SHUNT adc 15-default config value = " + String(rv));
      #endif
      
   }

   if(enabled_measures == MeasureEnabled::SHUNT) {
      if(measure_trigger == MeasureTrigger::ON_DEMAND) {
         MODE_MEASURE_SHUNT_ON_DEMAND(rv); 
         #ifdef DEBUG_CFG
         Serial.println("Only Shunt measure on demand config value = " + String(rv));
         #endif
         
      } else {
         MODE_MEASURE_SHUNT_CONTINUOS(rv);
         #ifdef DEBUG_CFG
         Serial.println("Only Shunt measure continuosly config value = " + String(rv));
         #endif
         
      }
   } else if(enabled_measures == MeasureEnabled::VOLTAGE) {
      if(measure_trigger == MeasureTrigger::ON_DEMAND) {
         MODE_MEASURE_BUS_ON_DEMAND(rv);
         #ifdef DEBUG_CFG
         Serial.println("Only BUS measure on demand config value = " + String(rv));
         #endif
         
      } else {
         MODE_MEASURE_BUS_CONTINUOS(rv);
         #ifdef DEBUG_CFG
         Serial.println("Only BUS measure continuosly config value = " + String(rv));
         #endif
         
      }
   } else if(enabled_measures == MeasureEnabled::BOTH_SHUNT_AND_VOLTAGE) {
      if(measure_trigger == MeasureTrigger::ON_DEMAND) {
         MODE_MEASURE_SHUNT_AND_BUS_ON_DEMAND(rv);
         #ifdef DEBUG_CFG
         Serial.println("BUS & SHUNT measure on demand config value = " + String(rv));
         #endif
         
      } else {
         MODE_MEASURE_SHUNT_AND_BUS_CONTINUOS(rv);
         #ifdef DEBUG_CFG
         Serial.println("BUS & SHUNT measure continuosly config value = " + String(rv));
         #endif
         
      }
   } else {
      #ifdef DEBUG_CFG
      Serial.println("BUS & SHUNT measure continuosly config value = " + String(rv));
      #endif
      MODE_MEASURE_SHUNT_AND_BUS_CONTINUOS(rv);
   }
   #ifdef DEBUG_CFG
   Serial.println("ENCODED CONFIGURATION = " + String(rv));
   Serial.println();
   #endif

   return rv;
}

/* __________________________________________________________________________ */
uint16_t ISL28022CfgClass::calc_calibration(float shunt_res_ohm) {
   float shunt_voltage_fs = 0.0;
   if(shunt_voltage_range == ShuntVoltageRange::RNG_40mv) {
      shunt_voltage_fs = FULL_SCALE_RANGE_040mv;
   } else if (shunt_voltage_range == ShuntVoltageRange::RNG_80mv) {
      shunt_voltage_fs = FULL_SCALE_RANGE_080mv;
   } else if (shunt_voltage_range == ShuntVoltageRange::RNG_160mv) {
      shunt_voltage_fs = FULL_SCALE_RANGE_160mv;
   } else {
      shunt_voltage_fs = FULL_SCALE_RANGE_320mv;
   }

   float resolution = 1.0;
   if(shunt_adc_cfg == AdcConf::CFG_12bit) {
      resolution = (1 << 12);
   } else if (shunt_adc_cfg == AdcConf::CFG_13bit) {
      resolution = (1 << 13);
   } else if (shunt_adc_cfg == AdcConf::CFG_14bit) {
      resolution = (1 << 14);
   } else {
      resolution = (1 << 15);
   } 

   float current_FS = shunt_voltage_fs / shunt_res_ohm;
   current_LSB = current_FS / resolution;
   float cal_reg = NUMERATOR_CALIB_REG / (shunt_res_ohm * current_LSB);

   return (uint16_t)cal_reg;
}


/* -------------------------------------------------------------------------- */
/*                    ISL28022Class implementation                            */
/* -------------------------------------------------------------------------- */

/* _______________________________________________________DEFAULT CONSTRUCTOR */
ISL28022Class::ISL28022Class(float _shunt_res_ohm) : 
   _wire(Wire), 
   slave_address(DEFAULT_SLAVE_ADDRESS),
   shunt_res_ohm(_shunt_res_ohm),
   cfg{_shunt_res_ohm} {
}

/* _______________________________________________________________CONSTRUCTOR */
ISL28022Class::ISL28022Class(float _shunt_res_ohm, TwoWire &w) : 
   _wire(w), 
   slave_address(DEFAULT_SLAVE_ADDRESS),
   shunt_res_ohm(_shunt_res_ohm),
   cfg{_shunt_res_ohm} {
}

/* _______________________________________________________________CONSTRUCTOR */
ISL28022Class::ISL28022Class(float _shunt_res_ohm, uint8_t a) : 
   _wire(Wire), 
   slave_address(a),
   shunt_res_ohm(_shunt_res_ohm),
   cfg{_shunt_res_ohm}{
}
 
/* _______________________________________________________________CONSTRUCTOR */ 
ISL28022Class::ISL28022Class(float _shunt_res_ohm, TwoWire &w, uint8_t a) :
    _wire(w), 
   slave_address(a),
   shunt_res_ohm(_shunt_res_ohm),
   cfg{_shunt_res_ohm} {
}

/* _______________________________________________________________DE-STRUCTOR */ 
ISL28022Class::~ISL28022Class() {}

/* ____________________________________________________________________send() */
void ISL28022Class::send(int add, uint8_t n, uint8_t r) {
   _wire.beginTransmission(add);
   for (int i = 0; i < n && i < TX_BUFFER_DIM; i++) {
      _wire.write(tx_buffer[i]);
      
   }
   _wire.endTransmission();
   if (r > 0) {
     _wire.requestFrom(add, r);
   }
}

/* _________________________________________________________________receive() */
bool ISL28022Class::receive(uint8_t n, uint16_t timeout) {
   uint8_t rx = 0;
   unsigned long int start = millis();
   while (millis() - start < timeout && rx < n) {
      while (_wire.available()) {
         uint8_t rec = _wire.read();
         if (rx < RX_BUFFER_DIM) {
            rx_buffer[rx++] = rec;
         }
      }
   }
   return (rx == n);
}

/* ___________________________________________________________________write() */
void ISL28022Class::write(uint8_t reg_add, uint16_t value) {
   tx_buffer[0] = reg_add;
   tx_buffer[1] = (uint8_t)((value >> 8) & 0xFF);
   tx_buffer[2] = (uint8_t)(value & 0xFF);
   send(slave_address, 3, 0);
}

/* ____________________________________________________________________read() */
uint16_t ISL28022Class::read(uint8_t reg_add) {
   uint16_t rv = 0;
   tx_buffer[0] = reg_add;
   send(slave_address, 1, 2);
   if(receive(2, READ_TIMEOUT)) {
      rv = rx_buffer[1];
      rv += rx_buffer[0] << 8; 
   }
   return rv;
}

/* ____________________________________________________________________bool() */
ISL28022Class::operator bool() {
   return initialized;
}


/* ___________________________________________________________________begin() */
bool ISL28022Class::begin() {
   _wire.begin();
   // the first time the configuration is written to reset the DEVICE
   uint16_t configuration = cfg.encode_config(true);
   write(ADD_CONFIGURATION_REG,configuration);
   
   // the second time the configuration is written to send the actual configuration
   configuration = cfg.encode_config(false);
   write(ADD_CONFIGURATION_REG,configuration);

   // then set the calibration register
   uint16_t calib_reg = cfg.calc_calibration(shunt_res_ohm);
   write(ADD_CALIBRATION_REG,calib_reg);
   initialized = true;
   return initialized;
}

/* ___________________________________________________________________begin() */
bool ISL28022Class::begin(ISL28022CfgClass &_cfg) {
   cfg = _cfg;
   begin();
   return initialized;
}


/* _______________________________________________________demand_conversion() */
uint16_t ISL28022Class::demand_conversion() {
   uint16_t bus_voltage_reg = 0;
   int max_attempt = 70; // max conversion time is 64 ms

   if(cfg.measure_trigger == MeasureTrigger::ON_DEMAND) {
      /* start the conversion */
      uint16_t configuration = cfg.encode_config(false);
      write(ADD_CONFIGURATION_REG,configuration);
   }
   else {
      /* read just once if not on demand */
      max_attempt = 1;
   }

   /* TODO: the conversion performed bit is present only in the bus 
            voltage. Does it works also for shunt since there is
            the same comfiguration? */

   while(max_attempt > 0) { // exit also when conversion is ready via break
      bus_voltage_reg = read(ADD_BUS_VOLTAGE_REG);
      max_attempt--;
      if(bus_voltage_reg & CONVERSION_READY_MASK) {
         break;
      }
      else if(max_attempt > 0){
         delay(1);
      }
   }
   
   return bus_voltage_reg;  
}


/* _________________________________________________________getShuntVoltage() */
float ISL28022Class::getShuntVoltage() {
   
   if(cfg.enabled_measures == MeasureEnabled::SHUNT || 
      cfg.enabled_measures == MeasureEnabled::BOTH_SHUNT_AND_VOLTAGE) {

      /* ask for a new conversion only if configured this way */
      demand_conversion();

      uint16_t shunt_voltage_reg = read(ADD_SHUNT_VOLTAGE_REG);

      int32_t shunt_voltage = 0; 

      /* TODO: from the datasheet it is not clear if the range used depends only
               from the ADC resolution or also from other setting (see TABEL.8 and
               following). TO BE VERIFIED! */

      if(cfg.shunt_adc_cfg == AdcConf::CFG_12bit) {
         shunt_voltage = two2int(shunt_voltage_reg, 12);
      } else if (cfg.shunt_adc_cfg == AdcConf::CFG_13bit) {
         shunt_voltage = two2int(shunt_voltage_reg, 13);
      } else if (cfg.shunt_adc_cfg == AdcConf::CFG_14bit) {
         shunt_voltage = two2int(shunt_voltage_reg, 14);
      } else {
         shunt_voltage = two2int(shunt_voltage_reg, 15);
      }

      return (float)shunt_voltage * SHUNT_LSB;
   }
   return 0.0;
}

/* ___________________________________________________________getBusVoltage() */
float ISL28022Class::getBusVoltage(bool &overflow) {
    if(cfg.enabled_measures == MeasureEnabled::VOLTAGE || 
       cfg.enabled_measures == MeasureEnabled::BOTH_SHUNT_AND_VOLTAGE) {

      uint16_t bus_voltage_reg = demand_conversion();
      overflow = (bus_voltage_reg & CONVERSION_OVERFLOW_MASK) ? true : false;
     
      /* TODO: it is not clear from the dataset if the reading start from 
               bit 2 or 3 
               there is a mismatch between the tables 12 14 and the formula
               in the next page. TO BE VERIFIED!  */

      bus_voltage_reg = bus_voltage_reg >> 2; // 2 or 3 ? 

      if(cfg.bus_adc_cfg == AdcConf::CFG_12bit) {
         bus_voltage_reg = bus_voltage_reg & ((1<<12) - 1); 
      } else if (cfg.bus_adc_cfg == AdcConf::CFG_13bit) {
         bus_voltage_reg = bus_voltage_reg & ((1<<13) - 1);   
      } else if (cfg.bus_adc_cfg == AdcConf::CFG_14bit) {
         bus_voltage_reg = bus_voltage_reg & ((1<<14) - 1);   
      } else {
         // seems 15 is not possible from datasheet (so 14)
         bus_voltage_reg = bus_voltage_reg & ((1<<14) - 1); 
      }

      return (float)bus_voltage_reg * BUS_LSB;
   }
   return 0.0; 
}

/* ______________________________________________________________getCurrent() */
float ISL28022Class::getCurrent() {
   uint16_t current_reg = read(ADD_CURRENT_REG);
   int32_t current = two2int(current_reg, 16);
   return (float)current * cfg.current_LSB;
}

/* ________________________________________________________________getPower() */
float ISL28022Class::getPower() {
   float power_LSB = cfg.current_LSB * BUS_LSB;
   uint16_t power_reg = read(ADD_POWER_REG);
   return (float)power_reg * power_LSB;
}

/* ________________________________________________setShuntVoltageThreshold() */
void ISL28022Class::setShuntVoltageThreshold(float low, float high) {
   float max_value = ((1 << 7) - 1) * SHUNT_TH_LSB;
   float min_value = -max_value;

   if(low > max_value) {
      low = max_value; 
   }
   if(low < min_value) {
      low = min_value;
   }

   if(high > max_value) {
      high = max_value; 
   }
   if(high < min_value) {
      high = min_value;
   }

   low = low / SHUNT_TH_LSB;
   high = high / SHUNT_TH_LSB;

   int32_t low_reg = (uint16_t)low;
   int32_t high_reg = (uint16_t)high;

   uint16_t low_reg_LSB =  int2two(low_reg, 8);
   uint16_t high_reg_MSB =  int2two(high_reg, 8);

   uint16_t shunt_th_reg = low_reg_LSB + (high_reg_MSB << 8);

   write(ADD_SHUNT_VOLTAGE_TH_REG, shunt_th_reg);
}

/* ________________________________________________________setBusThresholds() */
void ISL28022Class::setBusThresholds(float low, float high) {
   float max_value = ((1 << 7) - 1) * BUS_TH_LSB;
   float min_value = -max_value;

   if(low > max_value) {
      low = max_value; 
   }
   if(low < min_value) {
      low = min_value;
   }

   if(high > max_value) {
      high = max_value; 
   }
   if(high < min_value) {
      high = min_value;
   }

   low = low / BUS_TH_LSB;
   high = high / BUS_TH_LSB;

   uint16_t low_reg = (uint16_t)low;
   uint16_t high_reg = (uint16_t)high;

   uint16_t bus_th_reg = low_reg + (high_reg << 8);

   write(ADD_BUS_VOLTAGE_TH_REG, bus_th_reg);
}

/* ________________________________________________________busUnderThVoltage() */
bool ISL28022Class::busUnderThVoltage() {
   uint16_t th = read(ADD_DCS_INTERRUPT_STATUS_REG);
   if(th & BUS_LOWER_THRESHOLD_BIT_MASK) {
      write(ADD_DCS_INTERRUPT_STATUS_REG, BUS_LOWER_THRESHOLD_BIT_MASK);
      return true;
   }
   return false;
}

/* ________________________________________________________busOverThVoltage() */
bool ISL28022Class::busOverThVoltage() {
   uint16_t th = read(ADD_DCS_INTERRUPT_STATUS_REG);
   if(th & BUS_HIGHER_THRESHOLD_BIT_MASK) {
      write(ADD_DCS_INTERRUPT_STATUS_REG, BUS_HIGHER_THRESHOLD_BIT_MASK);
      return true;
   }
   return false;

}

/* _____________________________________________________shuntUnderThVoltage() */
bool ISL28022Class::shuntUnderThVoltage() {
   uint16_t th = read(ADD_DCS_INTERRUPT_STATUS_REG);
   if(th & SHUNT_LOWER_THRESHOLD_BIT_MASK) {
      write(ADD_DCS_INTERRUPT_STATUS_REG, SHUNT_LOWER_THRESHOLD_BIT_MASK);
      return true;
   }
   return false;
}

/* ______________________________________________________shuntOverThVoltage() */
bool ISL28022Class::shuntOverThVoltage() {
   uint16_t th = read(ADD_DCS_INTERRUPT_STATUS_REG);
   if(th & SHUNT_HIGHER_THRESHOLD_BIT_MASK) {
      write(ADD_DCS_INTERRUPT_STATUS_REG, SHUNT_HIGHER_THRESHOLD_BIT_MASK);
      return true;
   }
   return false;
}

/* _________________________________________________forceEXTCLK_INTpinToLow() */
void ISL28022Class::forceEXTCLK_INTpinToLow() {
   uint16_t aux_reg = 0;

   aux_reg |= AUX_FORCE_INTR;
   write(ADD_AUX_CONTROL_REG,aux_reg);
}

/* ____________________________________________useEXTCLK_INTpinForThreshold() */
void ISL28022Class::useEXTCLK_INTpinForThreshold() {
   uint16_t aux_reg = 0;

   aux_reg |= AUX_INTREN;
   write(ADD_AUX_CONTROL_REG,aux_reg);
}

/* ________________________________________________________useExternalClock() */
void ISL28022Class::useExternalClock(uint8_t div) {
   if(div > 63) {
      div = 63;
   }
   uint16_t aux_reg = 0;

   aux_reg |= div;
   aux_reg |= AUX_EXTCLK_ENABLE_BIT;

   write(ADD_AUX_CONTROL_REG,aux_reg);
}