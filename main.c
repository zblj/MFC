#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/dma.h"
#include "hardware/uart.h"
#include "hardware/pwm.h"

#include "boardDefines.h"
#include "peripheryFunctions.h"
#include "RS485.h"
#include "AD5592R.h"

/*
// Data will be copied from src to dst
const char src[] = "Hello, world! (from DMA)";
char dst[count_of(src)];

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 115200

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5
*/



int main()
{
    stdio_init_all();
    switchOutputsInit();
    RS485_init();
    MFCInit();

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, 1);

    // gpio_init(RS485_Tx_PIN);
    // gpio_set_dir(RS485_Tx_PIN, 1);

    // array of pins for iteration
    const int pins[] = {OUT_A_PIN,
                        OUT_B_PIN,
                        OUT_C_PIN,
                        OUT_D_PIN,
                        };
    uint16_t pwmLevel = 0;
    
    volatile uint16_t writeData = 0;
    volatile uint16_t readbackReg = 0;
    volatile uint16_t readbackVal = 0;

    while(0){
        AD5592R_Write(writeData);
        readbackVal = AD5592R_ReadReg(readbackReg);
    }
    
    volatile uint8_t ch = 0;
    volatile float DAC = 0;
    volatile float ADC = 0;
    while (true) {
        setMFC_volt(ch, DAC);
        ADC = readMFC_volt(ch);
    }
    while (true) {
        printf("Hello, world!\n");
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        // gpio_put(RS485_Tx_PIN, 1);
        sleep_ms(100);

        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        // gpio_put(RS485_Tx_PIN, 0);
        sleep_ms(100);

        RS485_transmit((uint8_t *)"abcd", 4);

        pwmLevel += 2048;
        for (int i=0; i<4; i++){
            // volatile uint16_t val = 0;
            // setSwitchOutput(i, val);
            setSwitchOutput(i, pwmLevel+i*4096);
            
        }

    }
}
