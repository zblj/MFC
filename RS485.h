#ifndef RS485_H
#define RS485_H
    #include <stdio.h>
    #include "pico/stdlib.h"
    #include "hardware/dma.h"
    #include "hardware/uart.h"
    #include "hardware/irq.h"

    #include "boardDefines.h"

    void RS485_init();
    int RS485_transmit(uint8_t *data, uint32_t len);
#endif