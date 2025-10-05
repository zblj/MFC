#ifndef PERIPHERYFUNCTIONS_H
#define PERIPHERYFUNCTIONS_H
    #include <stdio.h>
    #include "pico/stdlib.h"
    #include "hardware/spi.h"
    #include "hardware/dma.h"
    #include "hardware/uart.h"
    #include "hardware/pwm.h"

    #include "boardDefines.h"

    

    enum OutputChannel{
        CH_A,
        CH_B,
        CH_C,
        CH_D,
        CH_STOP,    /* Marker for the last element. */
    };

    extern uint8_t boardID;

    int switchOutputsInit( void );
    int setSwitchOutput(uint8_t ch, uint16_t val);

    void MFCInit(void);
    float readMFC_volt(uint8_t ch);
    void setMFC_volt(uint8_t ch, float volt);

    void boardIDSelector_Init(void);
    uint8_t boardIDSelector_getID(uint8_t setGlobalVariable);

#endif