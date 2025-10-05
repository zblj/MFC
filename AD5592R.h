#ifndef AD5592R_H
#define AD5592R_H
    // https://www.analog.com/media/en/technical-documentation/data-sheets/ad5592r.pdf

    #include "pico/stdlib.h"

    // AD5592R registers
    #define AD5592R_NOP                     ( 0<<11)        /* NOP. No operation. */
    #define AD5592R_DAC_RD                  ( 1<<11)        /* DAC Readback Register. Selects and enables DAC readback. */
    #define AD5592R_ADC_SEQ                 ( 2<<11)        /* ADC Sequence Register. Selects ADCs for conversion. */
    #define AD5592R_GEN_CTRL_REG            ( 3<<11)        /* General-Purpose Control Register. DAC and ADC control register. */
    #define AD5592R_ADC_CONFIG              ( 4<<11)        /* ADC Pin Configuration Register. Selects which pins are ADC inputs. */
    #define AD5592R_DAC_CONFIG              ( 5<<11)        /* DAC Pin Configuration Register. Selects which pins are DAC outputs. */
    #define AD5592R_PULLDWN_CONFIG          ( 6<<11)        /* Pull-Down Configuration Register. Selects which pins have an 85 kΩ pull-down resistor to GND. */
    #define AD5592R_CONFIG_READ_AND_LDAC    ( 7<<11)        /* Configuration Register readback and LDAC Mode Register. Selects the operation of the Load DAC (LDAC) function and/or which configuration register is read back. */
    #define AD5592R_GPIO_CONFIG             ( 8<<11)        /* GPIO Write Configuration Register. Selects which pins are general-purpose outputs. */
    #define AD5592R_GPIO_OUTPUT             ( 9<<11)        /* GPIO Write Data Register. Writes data to the general-purpose outputs. */
    #define AD5592R_GPIO_INPUT              (10<<11)        /* GPIO Read Configuration Register. Selects which pins are general-purpose inputs. */
    #define AD5592R_PD_REF_CTRL             (11<<11)        /* Power-Down/Reference Control Register. Powers down DACs and enables/disables the reference. */
    #define AD5592R_GPIO_OPENDRAIN_CONFIG   (12<<11)        /* GPIO Open-Drain Configuration Register. Selects open-drain or push/pull for general-purpose outputs. */
    #define AD5592R_IO_TS_CONFIG            (13<<11)        /* Three-State Configuration Register. Selects which pins are three-state. */
    #define AD5592R_SW_RESET                (15<<11)        /* Software Reset. Resets the AD5592R/AD5592R-1. */
    #define AD5592R_DAC_WR                  (0x8000)        /* DAC Write. Writes to addressed DAC register. Channel is selected by XXX at bits [14:11] */

    // AD5592R helper definitions
    #define AD5592R_DAC_WR_CH_BS            12              /* Channel select bit-shift ammount for DAC write operation. */
    
    int AD5592R_Write(uint16_t data);
    int AD5592R_Read(uint16_t *data);
    int AD5592R_Init(void);
    uint16_t AD5592R_ReadReg(uint16_t reg);

#endif