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

    // PWM enabled relay outputs
    int switchOutputsInit( void );
    int setSwitchOutput(uint8_t ch, uint16_t val);

    // MFC
    void MFCInit(void);
    float readMFC_volt(uint8_t ch);
    void setMFC_volt(uint8_t ch, float volt);

    // Board ID selector switch
    void boardIDSelector_Init(void);
    uint8_t boardIDSelector_getID(uint8_t setGlobalVariable);

    // ADC for supply voltage readback
    void PowerSupplyMonitor_Init(void);
    float PowerSupplyMonitor_read(uint8_t ch);

#endif