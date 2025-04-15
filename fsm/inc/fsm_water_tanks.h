#ifndef FSM_WATER_TANKS_H
#define FSM_WATER_TANKS_H

#include <stdbool.h>

// Definición de los estados de la FSM
typedef enum {
    STATE_IDLE,
    STATE_FILLING_RDWC,
    STATE_FILLING_TD,
    STATE_ALARM
} FSM_State_t;

// Estructura de la FSM
typedef struct {
    FSM_State_t state;
    bool sensor_rdwc_low;
    bool sensor_rdwc_high;
    bool sensor_td_low;
    bool sensor_td_high;
    bool flow_rdwc;
    bool flow_td;
    bool valve_rdwc;
    bool valve_td;
    unsigned int timer_rdwc;
    unsigned int timer_td;
} FSM_t;

// Funciones de la FSM
void FSM_Init(FSM_t *fsm);
void FSM_Reset(FSM_t *fsm);
void FSM_Update(FSM_t *fsm);
FSM_State_t FSM_GetState(FSM_t *fsm);

#endif // FSM_WATER_TANKS_H