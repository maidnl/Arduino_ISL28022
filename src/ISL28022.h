
/* This file contains the registers description for the ISL28022 device */

#ifndef ISL28022_REGISTER_DESCRIPTION
#define ISL28022_REGISTER_DESCRIPTION

/* Register addresses */
#define ADD_CONFIGURATION_REG           (0x00)
#define ADD_SHUNT_VOLTAGE_REG           (0x01)
#define ADD_BUS_VOLTAGE_REG             (0x02)
#define ADD_POWER_REG                   (0x03)
#define ADD_CURRENT_REG                 (0x04)
#define ADD_CALIBRATION_REG             (0x05)
#define ADD_SHUNT_VOLTAGE_TH_REG        (0x06)
#define ADD_BUS_VOLTAGE_TH_REG          (0x07)
#define ADD_DCS_INTERRUPT_STATUS_REG    (0x08)
#define ADD_AUX_CONTROL_REG             (0x09)


#define SHUNT_LSB           (0.000010) // 10 uV
#define BUS_LSB             (0.004)    // 4 mV
#define SHUNT_TH_LSB        (0.00256)  // 2.56 mV
#define BUS_TH_LSB          (0.256)    // 256 mV


#define CONVERSION_READY_MASK     (1 << 1)
#define CONVERSION_OVERFLOW_MASK (1 << 0)


#define SHUNT_LOWER_THRESHOLD_BIT_MASK (1 << 2)
#define SHUNT_HIGHER_THRESHOLD_BIT_MASK (1 << 3)

#define BUS_LOWER_THRESHOLD_BIT_MASK (1 << 0)
#define BUS_HIGHER_THRESHOLD_BIT_MASK (1 << 1)

#define AUX_EXTCLK_ENABLE_BIT (1 << 6)
#define AUX_FORCE_INTR        (1 << 8)
#define AUX_INTREN            (1 << 7)


#define FULL_SCALE_RANGE_320mv   (0.320)
#define FULL_SCALE_RANGE_160mv   (0.160)
#define FULL_SCALE_RANGE_080mv   (0.080)
#define FULL_SCALE_RANGE_040mv   (0.040) 
#define NUMERATOR_CALIB_REG      (0.04096)

#define MASK_3_BITS (0x07)
#define MASK_4_BITS (0x0F)
#define MASK_2_BITS (0x03)
#define MASK_1_BIT  (0x01)

#define POS_RESET_BIT                     (15)  // RESET
#define POS_BUS_VOLTAGE_RANGE_BIT         (13)  // BRNG
#define POS_SHUNT_VOLTAGE_ONLY_BIT        (11)  // PGA
#define POS_BUS_ADC_RESOLUTION_BIT        (07)  // BADC (Bus-ADC)
#define POS_SHUNT_RESOLUTION_BIT          (03)  // SADC (Shunt-ADC) 
#define POS_OPERATING_MODE_BIT            (00)  // MODE

#define BUS_VOLTAGE_RANGE_16_VAL           (0)
#define BUS_VOLTAGE_RANGE_32_VAL           (1)
#define BUS_VOLTAGE_RANGE_60_VAL           (3)

#define SHUNT_VOLTAGE_RANGE_40mv_VAL       (0)
#define SHUNT_VOLTAGE_RANGE_80mv_VAL       (1)
#define SHUNT_VOLTAGE_RANGE_160mv_VAL      (2)
#define SHUNT_VOLTAGE_RANGE_320mv_VAL      (3)

#define ADC_CONFIGURATION_REG_12b_VAL          (0)   // 12 bits
#define ADC_CONFIGURATION_REG_13b_VAL          (1)   // 13 bits
#define ADC_CONFIGURATION_REG_14b_VAL          (2)   // 14 bits
#define ADC_CONFIGURATION_REG_15b_VAL          (3)   // 15 bits
#define ADC_CONFIGURATION_REG_15b_AV1_VAL      (8)   // 15 bits (average on 1 sample ?)
#define ADC_CONFIGURATION_REG_15b_AV2_VAL      (9)   // 15 bits (average on 2 samples)
#define ADC_CONFIGURATION_REG_15b_AV4_VAL      (10)  // 15 bits (averaga on 4 samples)
#define ADC_CONFIGURATION_REG_15b_AV8_VAL      (11)  // 15 bits (averaga on 8 samples)
#define ADC_CONFIGURATION_REG_15b_AV16_VAL     (12)  // 15 bits (averaga on 16 samples)
#define ADC_CONFIGURATION_REG_15b_AV32_VAL     (13)  // 15 bits (averaga on 32 samples)
#define ADC_CONFIGURATION_REG_15b_AV64_VAL     (14)  // 15 bits (averaga on 64 samples)
#define ADC_CONFIGURATION_REG_15b_AV128_VAL    (15)  // 15 bits (averaga on 128 samples)

#define MODE_POWER_DOWN_VAL                         (0)
#define MODE_MEASURE_SHUNT_ON_DEMAND_VAL            (1)
#define MODE_MEASURE_BUS_ON_DEMAND_VAL              (2)
#define MODE_MEASURE_SHUNT_AND_BUS_ON_DEMAND_VAL    (3)
#define MODE_DISABLE_ADC_VAL                        (4)
#define MODE_MEASURE_SHUNT_CONTINUOS_VAL            (5)
#define MODE_MEASURE_BUS_CONTINUOS_VAL              (6)
#define MODE_MEASURE_SHUNT_AND_BUS_CONTINUOS_VAL    (7)         

#define SET_RESET_AND_CALIBRATE(x)        (x |=  (MASK_1_BIT << POS_RESET_BIT))
#define RESET_RESET_AND_CALIBRATE(x)      (x &= ~(MASK_1_BIT << POS_RESET_BIT))

/* always reset before to set */
#define RESET_BUS_VOLTAGE_RANGE(x)            (x &= ~(MASK_2_BITS << POS_BUS_VOLTAGE_RANGE_BIT))
#define BUS_VOLTAGE_RANGE_16V(x)          
#define BUS_VOLTAGE_RANGE_32V(x)          (x |=  (BUS_VOLTAGE_RANGE_32_VAL << POS_BUS_VOLTAGE_RANGE_BIT))
#define BUS_VOLTAGE_RANGE_60V(x)          (x |=  (BUS_VOLTAGE_RANGE_60_VAL << POS_BUS_VOLTAGE_RANGE_BIT))

/* always reset before to set */
#define RESET_PGA(x)                      (x &= ~(MASK_2_BITS << POS_SHUNT_VOLTAGE_ONLY_BIT))
#define SHUNT_VOLTAGE_RANGE_40mv(x)       (x |=  (SHUNT_VOLTAGE_RANGE_80mv_VAL << POS_SHUNT_VOLTAGE_ONLY_BIT)) 
#define SHUNT_VOLTAGE_RANGE_80mv(x)       (x |=  (SHUNT_VOLTAGE_RANGE_80mv_VAL << POS_SHUNT_VOLTAGE_ONLY_BIT))
#define SHUNT_VOLTAGE_RANGE_160mv(x)      (x |=  (SHUNT_VOLTAGE_RANGE_160mv_VAL << POS_SHUNT_VOLTAGE_ONLY_BIT))
#define SHUNT_VOLTAGE_RANGE_320mv(x)      (x |=  (SHUNT_VOLTAGE_RANGE_320mv_VAL << POS_SHUNT_VOLTAGE_ONLY_BIT))

/* always reset before to set */
#define RESET_BUS_ADC_SETTING(x)          (x &= ~(MASK_4_BITS << POS_BUS_ADC_RESOLUTION_BIT))
#define BUS_ADC_CFG_12b(x)                (x |=  (ADC_CONFIGURATION_REG_12b_VAL << POS_BUS_ADC_RESOLUTION_BIT))   
#define BUS_ADC_CFG_13b(x)                (x |=  (ADC_CONFIGURATION_REG_13b_VAL << POS_BUS_ADC_RESOLUTION_BIT))  
#define BUS_ADC_CFG_14b(x)                (x |=  (ADC_CONFIGURATION_REG_14b_VAL << POS_BUS_ADC_RESOLUTION_BIT))          
#define BUS_ADC_CFG_15b(x)                (x |=  (ADC_CONFIGURATION_REG_15b_VAL << POS_BUS_ADC_RESOLUTION_BIT))        
#define BUS_ADC_CFG_15b_AV1(x)            (x |=  (ADC_CONFIGURATION_REG_15b_AV1_VAL << POS_BUS_ADC_RESOLUTION_BIT))  
#define BUS_ADC_CFG_15b_AV2(x)            (x |=  (ADC_CONFIGURATION_REG_15b_AV2_VAL << POS_BUS_ADC_RESOLUTION_BIT))  
#define BUS_ADC_CFG_15b_AV4(x)            (x |=  (ADC_CONFIGURATION_REG_15b_AV4_VAL << POS_BUS_ADC_RESOLUTION_BIT))  
#define BUS_ADC_CFG_15b_AV8(x)            (x |=  (ADC_CONFIGURATION_REG_15b_AV8_VAL << POS_BUS_ADC_RESOLUTION_BIT))  
#define BUS_ADC_CFG_15b_AV16(x)           (x |=  (ADC_CONFIGURATION_REG_15b_AV16_VAL << POS_BUS_ADC_RESOLUTION_BIT))  
#define BUS_ADC_CFG_15b_AV32(x)           (x |=  (ADC_CONFIGURATION_REG_15b_AV32_VAL << POS_BUS_ADC_RESOLUTION_BIT))  
#define BUS_ADC_CFG_15b_AV64(x)           (x |=  (ADC_CONFIGURATION_REG_15b_AV64_VAL << POS_BUS_ADC_RESOLUTION_BIT))  
#define BUS_ADC_CFG_15b_AV128(x)          (x |=  (ADC_CONFIGURATION_REG_15b_AV128_VAL << POS_BUS_ADC_RESOLUTION_BIT))  

/* always reset before to set */
#define RESET_SHUNT_ADC_SETTING(x)         (x &= ~(MASK_4_BITS << POS_SHUNT_RESOLUTION_BIT))
#define SHUNT_ADC_CFG_12b(x)               (x |=  (ADC_CONFIGURATION_REG_13b_VAL << POS_SHUNT_RESOLUTION_BIT))     
#define SHUNT_ADC_CFG_13b(x)               (x |=  (ADC_CONFIGURATION_REG_13b_VAL << POS_SHUNT_RESOLUTION_BIT))  
#define SHUNT_ADC_CFG_14b(x)               (x |=  (ADC_CONFIGURATION_REG_14b_VAL << POS_SHUNT_RESOLUTION_BIT))          
#define SHUNT_ADC_CFG_15b(x)               (x |=  (ADC_CONFIGURATION_REG_15b_VAL << POS_SHUNT_RESOLUTION_BIT))        
#define SHUNT_ADC_CFG_15b_AV1(x)           (x |=  (ADC_CONFIGURATION_REG_15b_AV1_VAL << POS_SHUNT_RESOLUTION_BIT))  
#define SHUNT_ADC_CFG_15b_AV2(x)           (x |=  (ADC_CONFIGURATION_REG_15b_AV2_VAL << POS_SHUNT_RESOLUTION_BIT))  
#define SHUNT_ADC_CFG_15b_AV4(x)           (x |=  (ADC_CONFIGURATION_REG_15b_AV4_VAL << POS_SHUNT_RESOLUTION_BIT))  
#define SHUNT_ADC_CFG_15b_AV8(x)           (x |=  (ADC_CONFIGURATION_REG_15b_AV8_VAL << POS_SHUNT_RESOLUTION_BIT))  
#define SHUNT_ADC_CFG_15b_AV16(x)          (x |=  (ADC_CONFIGURATION_REG_15b_AV16_VAL << POS_SHUNT_RESOLUTION_BIT))  
#define SHUNT_ADC_CFG_15b_AV32(x)          (x |=  (ADC_CONFIGURATION_REG_15b_AV32_VAL << POS_SHUNT_RESOLUTION_BIT))  
#define SHUNT_ADC_CFG_15b_AV64(x)          (x |=  (ADC_CONFIGURATION_REG_15b_AV64_VAL << POS_SHUNT_RESOLUTION_BIT))  
#define SHUNT_ADC_CFG_15b_AV128(x)         (x |=  (ADC_CONFIGURATION_REG_15b_AV128_VAL << POS_SHUNT_RESOLUTION_BIT))

/* always reset before to set */
#define RESET_MODE(x)                             (x &= ~(MASK_3_BITS << POS_OPERATING_MODE_BIT))
#define MODE_POWER_DOWN(x)                        (x |=  (MODE_POWER_DOWN_VAL << POS_OPERATING_MODE_BIT))
#define MODE_MEASURE_SHUNT_ON_DEMAND(x)           (x |=  (MODE_MEASURE_SHUNT_ON_DEMAND_VAL << POS_OPERATING_MODE_BIT))
#define MODE_MEASURE_BUS_ON_DEMAND(x)             (x |=  (MODE_MEASURE_BUS_ON_DEMAND_VAL << POS_OPERATING_MODE_BIT))
#define MODE_MEASURE_SHUNT_AND_BUS_ON_DEMAND(x)   (x |=  (MODE_MEASURE_SHUNT_AND_BUS_ON_DEMAND_VAL << POS_OPERATING_MODE_BIT))
#define MODE_DISABLE_ADC(x)                       (x |=  (MODE_DISABLE_ADC_VAL << POS_OPERATING_MODE_BIT)) 
#define MODE_MEASURE_SHUNT_CONTINUOS(x)           (x |=  (MODE_MEASURE_SHUNT_CONTINUOS_VAL << POS_OPERATING_MODE_BIT))
#define MODE_MEASURE_BUS_CONTINUOS(x)             (x |=  (MODE_MEASURE_BUS_CONTINUOS_VAL << POS_OPERATING_MODE_BIT))
#define MODE_MEASURE_SHUNT_AND_BUS_CONTINUOS(x)   (x |=  (MODE_MEASURE_SHUNT_AND_BUS_CONTINUOS_VAL << POS_OPERATING_MODE_BIT))       



                                          


#endif



