#include "AD5592R.h"

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/irq.h"

#include "boardDefines.h"

int AD5592R_Write(uint16_t data){
    int error;
    gpio_put(AD5592R_CS, 0);  // CS
    error = spi_write16_blocking(SPI_PORT, &data, 1);
    gpio_put(AD5592R_CS, 1);  // !CS
    return error;
}
int AD5592R_Read(uint16_t *data){
    int error;
    gpio_put(AD5592R_CS, 0);  // CS
    error = spi_read16_blocking(SPI_PORT, 0, data, 1);
    gpio_put(AD5592R_CS, 1);  // !CS
    return error;
}
int AD5592R_Init(void){
    // Get SPI ready
    spi_init(SPI_PORT, SPI_FREQ);
    spi_set_format(SPI_PORT, 16, SPI_CPOL_1, SPI_CPHA_0, SPI_MSB_FIRST);
    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK , GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI , GPIO_FUNC_SPI);
    
    // prepare GPIOs
    gpio_init(AD5592R_CS);
    gpio_set_dir(AD5592R_CS, 1);
    gpio_put(AD5592R_CS, 1);

    gpio_init(AD5592R_RST);
    gpio_set_dir(AD5592R_RST, 1);
    gpio_put(AD5592R_RST, 1);

    // Reset AD5592R (could also call a soft reset)
    gpio_put(AD5592R_RST, 0);
    sleep_ms(1);
    gpio_put(AD5592R_RST, 1);
    sleep_ms(1);

    // Set ADC/DAC
    // Channels 2, 3, 4, and 5 are inputs
    //AD5592R_Write(AD5592R_ADC_SEQ | 0x003C);        // Make  the sequencer loop through channels 2-5 without repeating
    AD5592R_Write(AD5592R_GEN_CTRL_REG | (1<<8));   // Enable the ADC buffer
    AD5592R_Write(AD5592R_ADC_CONFIG | 0x003C);     // Set ADC on channels 2-5
    AD5592R_Write(AD5592R_DAC_CONFIG | 0x00C3);     // Set DAC on channels 0,1, 6, and 7
    AD5592R_Write(AD5592R_PULLDWN_CONFIG | 0);      // Disable pulldown reistors
    AD5592R_Write(AD5592R_PD_REF_CTRL | (1<<9));      // Enable internal reference

    // Some error handling would be in order, but who am I kidding...
    return 0;
}

uint16_t AD5592R_ReadReg(uint16_t reg){
    uint16_t val;
    if (reg > AD5592R_DAC_RD){
        reg = reg>>11;
    }
    AD5592R_Write(AD5592R_CONFIG_READ_AND_LDAC  | 1<<6 | reg<<2);
    sleep_us(1);
    AD5592R_Read(&val);
    return val;
}

