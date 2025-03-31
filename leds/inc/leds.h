#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Inicializa el módulo de LEDs, apagando todos los LEDs.
 * @param direccion Puntero a la variable donde se almacenará el estado de los LEDs.
 */
void LedsInit(uint16_t* direccion);

/**
 * @brief Enciende un LED específico.
 * @param led Número de LED a encender (1 a 16).
 */
void LedsTurnOnSingle(uint8_t led);

/**
 * @brief Apaga un LED específico.
 * @param led Número de LED a apagar (1 a 16).
 */
void LedsTurnOffSingle(uint8_t led);

/**
 * @brief Enciende todos los LEDs.
 */
void LedsTurnOnAllLeds(void);

/**
 * @brief Apaga todos los LEDs.
 */
void LedsTurnOffAllLeds(void);

/**
 * @brief Verifica si un LED está encendido.
 * @param led Número de LED a consultar (1 a 16).
 * @return true si el LED está encendido, false si está apagado.
 */
bool IsLedTurnedOn(uint8_t led);

#endif // LEDS_H