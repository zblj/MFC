#include "RS485.h"

void RS485_init(){
    gpio_init(RS485_TR_PIN);
    gpio_set_dir(RS485_TR_PIN, 1);
    gpio_put(RS485_TR_PIN, 0);  // enable receiver, disable transmitter

    gpio_set_function(RS485_Tx_PIN, GPIO_FUNC_UART);
    gpio_set_function(RS485_Rx_PIN, GPIO_FUNC_UART);
    
    // Set up our UART with a basic baud rate.
    uart_init(RS485_PORT, RS485_BAUD);

    // Set baud and returns actual baud
    // int actualBaudrate = uart_set_baudrate(RS485_PORT, RS485_BAUD);

    // Set UART flow control CTS/RTS, we don't want these, so turn them off
    uart_set_hw_flow(RS485_PORT, false, false);

    // Set our data format
    uart_set_format(RS485_PORT, RS485_DATA_BITS, RS485_STOP_BITS, RS485_PARITY);

    // Turn off FIFO's - we want to do this character by character
    uart_set_fifo_enabled(RS485_PORT, false);
}
int RS485_transmit(uint8_t *data, uint32_t len){
    gpio_put(RS485_TR_PIN, 1);  // enable transmitter, disable receiver
    uart_write_blocking(RS485_PORT, data, len);
    uart_tx_wait_blocking(RS485_PORT);
    gpio_put(RS485_TR_PIN, 0);  // enable receiver, disable transmitter
    return 0;
}