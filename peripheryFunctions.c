#include "peripheryFunctions.h"
#include "AD5592R.h"
#include "math.h"

#ifndef MAX
    #define MAX(x, y) (((x) > (y)) ? (x) : (y))
#endif
#ifndef MIN
    #define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif

struct{
    float ADC_gain[4];
    float ADC_offset[4];
    float DAC_gain[4];
    float DAC_offset[4];
} calibrationData;

int switchOutputsInit( void ){
    // array of pins for iteration
    const int pins[] = {OUT_A_PIN,
                        OUT_B_PIN,
                        OUT_C_PIN,
                        OUT_D_PIN,
                        };
    const uint8_t div_int = 1;
    const uint8_t div_frac = 1;
    const uint16_t wrap = 0xFFFF;   // up to 16b
    
    // Set GPIO function and PWM parameters for each cahnnel
    for (int i=0; i<(sizeof(pins)/sizeof(pins[0])); i++){
        gpio_set_function(pins[i], GPIO_FUNC_PWM);
        pwm_set_clkdiv_int_frac(pwm_gpio_to_slice_num(pins[i]), div_int, div_frac);
        pwm_set_wrap(pwm_gpio_to_slice_num(pins[i]), wrap);
        pwm_set_chan_level(pwm_gpio_to_slice_num(pins[i]), pwm_gpio_to_channel(pins[i]), 0);
        pwm_set_enabled(pwm_gpio_to_slice_num(pins[i]), 1);
    }
    return 0;
}

int setSwitchOutput(uint8_t ch, uint16_t val){
    const uint8_t channelPins[] = {OUT_A_PIN, OUT_B_PIN, OUT_C_PIN, OUT_D_PIN};

    // Check if channel is out of range
    if (ch >= CH_STOP){
        return 1;
    }

    pwm_set_chan_level(pwm_gpio_to_slice_num(channelPins[ch]), pwm_gpio_to_channel(channelPins[ch]), val);
    return 0;
}

void MFCInit(void){
    for (int i=0; i<4; i++){
        calibrationData.ADC_gain[i] = 1;
        calibrationData.ADC_offset[i] = 0;
        calibrationData.DAC_gain[i] = 1;
        calibrationData.DAC_offset[i] = 0;
    }
    AD5592R_Init();
}

float readMFC_volt(uint8_t ch){
    uint16_t reading;
    float voltage;
    uint8_t channelID;
    const uint16_t channelIDs[] = {3, 2, 5, 4};

    // Cathch the possible "beyond scope" channel
    if (ch > 3){
        return NAN;
    }

    // Prepare for reading and wait through the period of tracking time
    AD5592R_Write(AD5592R_ADC_SEQ | (1<<(channelIDs[ch]))); // Writing to sequencer initiates the reading
    // sleep_us(20);   // without input buffer
    sleep_us(5);    // with input buffer

    // dummy transfer
    AD5592R_Write(0); // Writing to sequencer initiates the reading

    // actually read the value
    AD5592R_Read(&reading);

    // check if correct channel was read back
    channelID = reading >> 12;
    if (channelIDs[ch] != channelID){
        return NAN;
    }

    // convert code to voltage
    voltage = reading & 0x0FFF;
    voltage *= 5./4096.;
    voltage -= calibrationData.ADC_offset[ch];
    voltage *= calibrationData.ADC_gain[ch];
    
    return voltage;
}
void setMFC_volt(uint8_t ch, float volt){
    int voltCode;
    const uint16_t channelIDs[] = {1, 0, 7, 6};
    volt -= calibrationData.DAC_offset[ch];
    volt *= calibrationData.DAC_gain[ch];
    volt *= 4096./5.;
    volt = roundf(volt);

    voltCode = MAX(0, MIN(volt, 4095));

    AD5592R_Write(AD5592R_DAC_WR | ((channelIDs[ch])<<12) | voltCode); // Writing to sequencer initiates the reading
}