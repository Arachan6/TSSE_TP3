#include "unity.h"
#include "leds.h"

static uint16_t leds_virtuales = 0xFFFF;

/// @brief Configuración inicial antes de cada test
void setUp(void) {
    LedsInit(&leds_virtuales);
}

/// @test Con la inicialización, todos los LEDs deben quedar apagados
void test_todos_los_leds_inician_apagados(void) {
    uint16_t leds_virtuales = 0xFFFF;
    LedsInit(&leds_virtuales);
    TEST_ASSERT_EQUAL_HEX16(0x0000, leds_virtuales);
}

/// @test Prender un LED individual
void test_prender_led_individual(void) {
    LedsTurnOnSingle(4);
    TEST_ASSERT_EQUAL_HEX16(0x0008, leds_virtuales);
}

/// @test Apagar un LED individual
void test_apagar_led_individual(void) {
    LedsTurnOnSingle(4);
    LedsTurnOffSingle(4);
    TEST_ASSERT_EQUAL_HEX16(0x0000, leds_virtuales);
}

/// @test Prender y apagar algunos LEDs
void test_prender_y_apagar_algunos_leds(void) {
    LedsTurnOnSingle(4);
    LedsTurnOnSingle(6);
    LedsTurnOffSingle(4);
    LedsTurnOffSingle(8);
    TEST_ASSERT_EQUAL_HEX16(0x0020, leds_virtuales);
}

/// @test Prender todos los LEDs de una vez
void test_prender_todos_los_leds(void) {
    LedsTurnOnAllLeds();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, leds_virtuales);
}

/// @test Apagar todos los LEDs de una vez
void test_apagar_todos_los_leds(void) {
    LedsTurnOnAllLeds();
    LedsTurnOffAllLeds();
    TEST_ASSERT_EQUAL_HEX16(0x0000, leds_virtuales);
}

/// @test Consultar el estado de un LED encendido
void test_consultar_led_encendido(void) {
    LedsTurnOnSingle(5);
    TEST_ASSERT_TRUE(IsLedTurnedOn(5));
}

/// @test Consultar el estado de un LED apagado
void test_consultar_led_apagado(void) {
    TEST_ASSERT_FALSE(IsLedTurnedOn(3));
}

/// @test Revisar límites de los parámetros
void test_revisar_limites_parametros(void) {
    LedsTurnOnSingle(1);
    LedsTurnOnSingle(16);
    TEST_ASSERT_TRUE(IsLedTurnedOn(1));
    TEST_ASSERT_TRUE(IsLedTurnedOn(16));
}

/// @test Revisar parámetros fuera de los límites
void test_parametros_fuera_de_limites(void) {
    LedsTurnOnSingle(0);
    LedsTurnOnSingle(17);
    TEST_ASSERT_FALSE(IsLedTurnedOn(0));
    TEST_ASSERT_FALSE(IsLedTurnedOn(17));
}
