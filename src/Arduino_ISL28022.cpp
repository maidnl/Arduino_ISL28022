#include "Arduino_ISL28022.h"

/* __________________________________________________________________________ */
uint16_t ISL28022CfgClass::encodeConfig(bool reset) {
   uint16_t rv = 0;
   if(reset) {
      SET_RESET_AND_CALIBRATE(rv);
   }
   if(bus_voltage_range == BusVoltageRange::RNG_16V) {
      BUS_VOLTAGE_RANGE_16V(rv);
   } else if (bus_voltage_range == BusVoltageRange::RNG_32V) {
      BUS_VOLTAGE_RANGE_32V(rv);
   } else {
      BUS_VOLTAGE_RANGE_60V(rv);
   }

   if(shunt_voltage_range == ShuntVoltageRange::RNG_40mv) {
      SHUNT_VOLTAGE_RANGE_40mv(rv);
   } else if (shunt_voltage_range == ShuntVoltageRange::RNG_80mV) {
      SHUNT_VOLTAGE_RANGE_80mv(rv);
   } else if (shunt_voltage_range == ShuntVoltageRange::RNG_160mv) {
      SHUNT_VOLTAGE_RANGE_160mv(rv);
   } else {
      SHUNT_VOLTAGE_RANGE_320mv(rv);
   }

   if(bus_adc_cfg == AdcConf::CFG_12bit) {
      BUS_ADC_CFG_12b(rv);
   } else if (bus_adc_cfg == AdcConf::CFG_13bit) {
      BUS_ADC_CFG_13b(rv);
   } else if (bus_adc_cfg == AdcConf::CFG_14bit) {
      BUS_ADC_CFG_14b(rv);
   } else if (bus_adc_cfg == AdcConf::CFG_15bit) {
      BUS_ADC_CFG_15b(rv);
   } else if (bus_adc_cfg == AdcConf::CFG_15bit_with_1average) {
      BUS_ADC_CFG_15b_AV1(rv);
   } else if (bus_adc_cfg == AdcConf::CFG_15bit_with_2average) {
      BUS_ADC_CFG_15b_AV2(rv);
   } else if (bus_adc_cfg == AdcConf::CFG_15bit_with_4average) {
      BUS_ADC_CFG_15b_AV4(rv);
   } else if (bus_adc_cfg == AdcConf::CFG_15bit_with_8average) {
      BUS_ADC_CFG_15b_AV8(rv);
   } else if (bus_adc_cfg == AdcConf::CFG_15bit_with_16average) {
      BUS_ADC_CFG_15b_AV16(rv);
   } else if (bus_adc_cfg == AdcConf::CFG_15bit_with_32average) {
      BUS_ADC_CFG_15b_AV32(rv);
   } else if (bus_adc_cfg == AdcConf::CFG_15bit_with_64average) {
      BUS_ADC_CFG_15b_AV64(rv);
   } else if (bus_adc_cfg == AdcConf::CFG_15bit_with_128average) {
      BUS_ADC_CFG_15b_AV128(rv);
   } else {
      BUS_ADC_CFG_15b(rv);
   }

   if(shunt_adc_cfg == AdcConf::CFG_12bit) {
      SHUNT_ADC_CFG_12b(rv);
   } else if (shunt_adc_cfg == AdcConf::CFG_13bit) {
      SHUNT_ADC_CFG_13b(rv);
   } else if (shunt_adc_cfg == AdcConf::CFG_14bit) {
      SHUNT_ADC_CFG_14b(rv);
   } else if (shunt_adc_cfg == AdcConf::CFG_15bit) {
      SHUNT_ADC_CFG_15b(rv);
   } else if (shunt_adc_cfg == AdcConf::CFG_15bit_with_1average) {
      SHUNT_ADC_CFG_15b_AV1(rv);
   } else if (shunt_adc_cfg == AdcConf::CFG_15bit_with_2average) {
      SHUNT_ADC_CFG_15b_AV2(rv);
   } else if (shunt_adc_cfg == AdcConf::CFG_15bit_with_4average) {
      SHUNT_ADC_CFG_15b_AV4(rv);
   } else if (shunt_adc_cfg == AdcConf::CFG_15bit_with_8average) {
      SHUNT_ADC_CFG_15b_AV8(rv);
   } else if (shunt_adc_cfg == AdcConf::CFG_15bit_with_16average) {
      SHUNT_ADC_CFG_15b_AV16(rv);
   } else if (shunt_adc_cfg == AdcConf::CFG_15bit_with_32average) {
      SHUNT_ADC_CFG_15b_AV32(rv);
   } else if (shunt_adc_cfg == AdcConf::CFG_15bit_with_64average) {
      SHUNT_ADC_CFG_15b_AV64(rv);
   } else if (shunt_adc_cfg == AdcConf::CFG_15bit_with_128average) {
      SHUNT_ADC_CFG_15b_AV128(rv);
   } else {
      SHUNT_ADC_CFG_15b(rv);
   }

   if(enabled_measures == MeasureEnabled::SHUNT) {
      if(measure_trigger == MeasureTrigger::ON_DEMAND) {
         MODE_MEASURE_SHUNT_ON_DEMAND(rv); 
      } else {
         MODE_MEASURE_SHUNT_CONTINUOS(rv);
      }
   } else if(enabled_measures == MeasureEnabled::VOLTAGE) {
      if(measure_trigger == MeasureTrigger::ON_DEMAND) {
         MODE_MEASURE_BUS_ON_DEMAND(rv);
      } else {
         MODE_MEASURE_BUS_CONTINUOS(rv);
      }
   } else if(enabled_measures == MeasureEnabled::BOTH_SHUNT_AND_VOLTAGE) {
      if(measure_trigger == MeasureTrigger::ON_DEMAND) {
         MODE_MEASURE_SHUNT_AND_BUS_ON_DEMAND(rv);
      } else {
         MODE_MEASURE_SHUNT_AND_BUS_CONTINUOS(rv);
      }
   } else {
      MODE_MEASURE_SHUNT_AND_BUS_CONTINUOS(rv);
   }
   return rv;
}



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

/* _______________________________________________________DEFAULT CONSTRUCTOR */
ISL28022Class::ISL28022Class(float _shunt_res_ohm) : 
   _wire(Wire), 
   slave_address(DEFAULT_SLAVE_ADDRESS),
   shunt_res_ohm(_shunt_res_ohm) {
}

/* _______________________________________________________________CONSTRUCTOR */
ISL28022Class::ISL28022Class(float _shunt_res_ohm, TwoWire &w) : 
   _wire(w), 
   slave_address(DEFAULT_SLAVE_ADDRESS),
   shunt_res_ohm(_shunt_res_ohm) {
}

/* _______________________________________________________________CONSTRUCTOR */
ISL28022Class::ISL28022Class(float _shunt_res_ohm, uint8_t a) : 
   _wire(Wire), 
   slave_address(a),
   shunt_res_ohm(_shunt_res_ohm){
}
 
/* _______________________________________________________________CONSTRUCTOR */ 
ISL28022Class::ISL28022Class(float _shunt_res_ohm, TwoWire &w, uint8_t a) :
    _wire(w), 
   slave_address(a),
   shunt_res_ohm(_shunt_res_ohm){
}

/* _______________________________________________________________DE-STRUCTOR */ 
ISL28022Class::~ISL28022Class() {}

/* ____________________________________________________________________send() */
void ISL28022Class::send(int add, uint8_t n, uint8_t r) {
   Wire.beginTransmission(add);
   for (int i = 0; i < n && i < TX_BUFFER_DIM; i++) {
      Wire.write(tx_buffer[i]);
   }
   Wire.endTransmission();
   if (r > 0) {
     Wire.requestFrom(add, r);
   }
}

/* _________________________________________________________________receive() */
bool ISL28022Class::receive(uint8_t n, uint16_t timeout) {
   uint8_t rx = 0;
   unsigned long int start = millis();
   while (millis() - start < timeout && rx < n) {
      while (Wire.available()) {
         uint8_t rec = Wire.read();
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
   tx_buffer[1] = (uint8_t)((value >> 8) & 0xF);
   tx_buffer[2] = (uint8_t)(value & 0xF);
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

/* ___________________________________________________________________begin() */
bool ISL28022Class::begin() {
   uint16_t configuration = cfg.encodeConfig(true);
   write(ADD_CONFIGURATION_REG,configuration);
   return true;
}

/* ___________________________________________________________________begin() */
bool ISL28022Class::begin(ISL28022CfgClass &_cfg) {
   cfg = _cfg;
   begin();
   return true;

}


/* _________________________________________________________getShuntVoltage() */
float ISL28022Class::getShuntVoltage() {
   return 1.0;
}