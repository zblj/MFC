#ifndef BOARDDEFINITIONS_H
#define BOARDDEFINITIONS_H
    // SPI
    #define SPI_PORT spi0
    #define SPI_FREQ 1e6
    #define PIN_MISO 0
    #define PIN_SCK  2
    #define PIN_MOSI 3
    
    // AD5592
    #define AD5592R_CS 1
    #define AD5592R_RST 4
    
    // RS485
    #define RS485_TR_PIN 18
    #define RS485_Tx_PIN 16
    #define RS485_Rx_PIN 17
    #define RS485_PORT uart0
    #define RS485_BAUD 9600
    #define RS485_DATA_BITS 8
    #define RS485_STOP_BITS 1
    #define RS485_PARITY UART_PARITY_NONE

    // PWM enabled output pins
    #define OUT_A_PIN 5   /* OUT 1 */
    #define OUT_B_PIN 6   /* OUT 2 */  
    #define OUT_C_PIN 7   /* OUT 3 */
    #define OUT_D_PIN 8   /* OUT 4 */

    // PSU sense
    #define VN_SNS_CH  2
    #define VP_SNS_CH  1
    #define VIN_SNS_CH 0

    // Board ID
    #define ID_PIN_1 19
    #define ID_PIN_2 21
    #define ID_PIN_3 22
    #define ID_PIN_4 20
    #define BOARD_ID 0x00   /* top nibble is fixed, lower nibble is overriden by ID pins */

#endif