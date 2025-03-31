#include "leds.h"

#define ALL_LEDS_OFF        0x0000
#define ALL_LEDS_ON         0xFFFF
#define LEDS_TO_BIT_OFFSET  1
#define FIRST_BIT           1
#define MIN_LED             1
#define MAX_LED             16

static uint16_t *port_address;

/**
 * @brief Convierte un número de LED a su correspondiente máscara de bits.
 * @param led Número de LED (1 a 16).
 * @return Máscara de bits correspondiente al LED.
 */
static uint16_t LedToMask(uint8_t led){
    return (FIRST_BIT << (led - LEDS_TO_BIT_OFFSET));
}

void LedsInit(uint16_t* direccion){
    port_address = direccion;
    *port_address = ALL_LEDS_OFF;
}

void LedsTurnOnSingle(uint8_t led){
    if (led < MIN_LED || led > MAX_LED) return;
    *port_address |= LedToMask(led);
}

void LedsTurnOffSingle(uint8_t led){
    if (led < MIN_LED || led > MAX_LED) return;
    *port_address &= ~LedToMask(led);
}

void LedsTurnOnAllLeds(void){
    *port_address = ALL_LEDS_ON;
}

void LedsTurnOffAllLeds(void){
    *port_address = ALL_LEDS_OFF;
}

bool IsLedTurnedOn(uint8_t led){
    if (led < MIN_LED || led > MAX_LED) return false;
    return (*port_address & LedToMask(led)) != 0;
}
