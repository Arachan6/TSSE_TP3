#include "fsm_water_tanks.h"

// Inicializa la FSM
void FSM_Init(FSM_t *fsm) {
    fsm->state = STATE_IDLE;
    fsm->sensor_rdwc_low = false;
    fsm->sensor_rdwc_high = false;
    fsm->sensor_td_low = false;
    fsm->sensor_td_high = false;
    fsm->flow_rdwc = false;
    fsm->flow_td = false;
    fsm->valve_rdwc = false;
    fsm->valve_td = false;
    fsm->timer_rdwc = 0;
    fsm->timer_td = 0;
}

// Resetea la FSM a estado IDLE
void FSM_Reset(FSM_t *fsm) {
    FSM_Init(fsm);
}

// Actualiza el estado de la FSM
void FSM_Update(FSM_t *fsm) {
    switch (fsm->state) {
        case STATE_IDLE:
            if (fsm->sensor_rdwc_low) {
                fsm->valve_rdwc = true;
                fsm->timer_rdwc = 0;
                fsm->state = STATE_FILLING_RDWC;
            } else if (fsm->sensor_td_low) {
                fsm->valve_td = true;
                fsm->timer_td = 0;
                fsm->state = STATE_FILLING_TD;
            }
            break;
        
        case STATE_FILLING_RDWC:
            fsm->timer_rdwc++;
            if (fsm->sensor_rdwc_high) {
                fsm->valve_rdwc = false;
                if (fsm->sensor_td_low) {
                    fsm->valve_td = true;
                    fsm->state = STATE_FILLING_TD;
                } else {
                    fsm->state = STATE_IDLE;
                }
            } else if (fsm->timer_rdwc > 10000 && !fsm->flow_rdwc) {
                fsm->valve_rdwc = false;
                fsm->state = STATE_ALARM;
            }
            break;
        
        case STATE_FILLING_TD:
            fsm->timer_td++;
            if (fsm->sensor_td_high) {
                fsm->valve_td = false;
                fsm->state = STATE_IDLE;
            } else if (fsm->timer_td > 10000 && !fsm->flow_td) {
                fsm->valve_td = false;
                fsm->state = STATE_ALARM;
            }
            break;
        
        case STATE_ALARM:
            fsm->valve_rdwc = false;
            fsm->valve_td = false;
            // Espera a ser reseteada manualmente
            break;
    }
}

// Obtiene el estado actual de la FSM
FSM_State_t FSM_GetState(FSM_t *fsm) {
    return fsm->state;
}