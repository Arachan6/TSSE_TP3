#include "unity.h"
#include "fsm_water_tanks.h"

FSM_t fsm_test;  // Instance of FSM_t for testing

// Set up function
void setUp(void) {
    FSM_Init(&fsm_test);  // Initialize FSM before each test
}

// Test: FSM should start in IDLE state with all fields false
void test_FSM_Init(void) {
    TEST_ASSERT_EQUAL(STATE_IDLE, fsm_test.state);
    TEST_ASSERT_FALSE(fsm_test.sensor_rdwc_low);
    TEST_ASSERT_FALSE(fsm_test.sensor_rdwc_high);
    TEST_ASSERT_FALSE(fsm_test.sensor_td_low);
    TEST_ASSERT_FALSE(fsm_test.sensor_td_high);
    TEST_ASSERT_FALSE(fsm_test.flow_rdwc);
    TEST_ASSERT_FALSE(fsm_test.flow_td);
    TEST_ASSERT_FALSE(fsm_test.valve_rdwc);
    TEST_ASSERT_FALSE(fsm_test.valve_td);
    TEST_ASSERT_EQUAL(0, fsm_test.timer_rdwc);
    TEST_ASSERT_EQUAL(0, fsm_test.timer_td);
}

// Test: FSM should transition to FILLING_RDWC when RDWC low sensor is triggered
void test_FSM_Update_to_Filling_RDWC(void) {
    fsm_test.sensor_rdwc_low = true;
    FSM_Update(&fsm_test);  // Call FSM_Update with sensor_rdwc_low as true
    TEST_ASSERT_EQUAL(STATE_FILLING_RDWC, fsm_test.state);
    TEST_ASSERT_TRUE(fsm_test.valve_rdwc);
    TEST_ASSERT_EQUAL(0, fsm_test.timer_rdwc);
}

// Test: FSM should transition to FILLING_TD if RDWC is already full and TD low sensor is triggered
void test_FSM_Update_to_Filling_TD(void) {
    fsm_test.sensor_rdwc_high = true;
    fsm_test.sensor_td_low = true;
    fsm_test.state = STATE_FILLING_RDWC;  // Set initial state to FILLING_RDWC
    FSM_Update(&fsm_test);
    TEST_ASSERT_EQUAL(STATE_FILLING_TD, fsm_test.state);
    TEST_ASSERT_TRUE(fsm_test.valve_td);
    TEST_ASSERT_EQUAL(0, fsm_test.timer_td);
}

// Test: FSM should go to ALARM if RDWC filling takes too long (timeout)
void test_FSM_Update_to_Alarm_RDWCTimeout(void) {
    fsm_test.state = STATE_FILLING_RDWC;
    fsm_test.timer_rdwc = 10001;  // Set timer to simulate timeout
    FSM_Update(&fsm_test);
    TEST_ASSERT_EQUAL(STATE_ALARM, fsm_test.state);
    TEST_ASSERT_FALSE(fsm_test.valve_rdwc);
}

// Test: FSM should go to ALARM if TD filling takes too long (timeout)
void test_FSM_Update_to_Alarm_TDTimeout(void) {
    fsm_test.state = STATE_FILLING_TD;
    fsm_test.timer_td = 10001;  // Set timer to simulate timeout
    FSM_Update(&fsm_test);
    TEST_ASSERT_EQUAL(STATE_ALARM, fsm_test.state);
    TEST_ASSERT_FALSE(fsm_test.valve_td);
}

// Test: FSM should return to IDLE after RDWC is filled and TD sensor triggers
void test_FSM_Update_to_IDLE_after_Filling_TD(void) {
    fsm_test.state = STATE_FILLING_RDWC;
    fsm_test.sensor_rdwc_high = true;
    fsm_test.sensor_td_low = true;
    FSM_Update(&fsm_test);
    TEST_ASSERT_EQUAL(STATE_FILLING_TD, fsm_test.state);  // Ensure transition to TD filling
}

// Test: FSM should remain in ALARM state until reset
void test_FSM_AlarmState(void) {
    fsm_test.state = STATE_ALARM;
    FSM_Update(&fsm_test);
    TEST_ASSERT_EQUAL(STATE_ALARM, fsm_test.state);
    TEST_ASSERT_FALSE(fsm_test.valve_rdwc);
    TEST_ASSERT_FALSE(fsm_test.valve_td);
}

// Test: FSM should reset to IDLE state when reset function is called
void test_FSM_Reset(void) {
    fsm_test.state = STATE_FILLING_RDWC;
    FSM_Reset(&fsm_test);  // Call reset function
    TEST_ASSERT_EQUAL(STATE_IDLE, fsm_test.state);
}

// Test: Ensure that FSM handles the transition between states properly
void test_FSM_StateTransition(void) {
    fsm_test.sensor_rdwc_low = true;
    FSM_Update(&fsm_test);
    TEST_ASSERT_EQUAL(STATE_FILLING_RDWC, fsm_test.state);

    fsm_test.sensor_rdwc_high = true;
    FSM_Update(&fsm_test);
    TEST_ASSERT_EQUAL(STATE_IDLE, fsm_test.state);

    fsm_test.sensor_rdwc_low = false;
    fsm_test.sensor_td_low = true;
    FSM_Update(&fsm_test);
    TEST_ASSERT_EQUAL(STATE_FILLING_TD, fsm_test.state);
}

// Test: FSM_GetState should return STATE_IDLE after initialization
void test_FSM_GetState_Initial(void) {
    TEST_ASSERT_EQUAL(STATE_IDLE, FSM_GetState(&fsm_test));
}

// Test: FSM_GetState should return the correct state after transitions
void test_FSM_GetState_Transitions(void) {
    fsm_test.sensor_rdwc_low = true;
    FSM_Update(&fsm_test);
    TEST_ASSERT_EQUAL(STATE_FILLING_RDWC, FSM_GetState(&fsm_test));

    fsm_test.sensor_rdwc_high = true;
    FSM_Update(&fsm_test);
    TEST_ASSERT_EQUAL(STATE_IDLE, FSM_GetState(&fsm_test));

    fsm_test.sensor_rdwc_low = false;
    fsm_test.sensor_td_low = true;
    FSM_Update(&fsm_test);
    TEST_ASSERT_EQUAL(STATE_FILLING_TD, FSM_GetState(&fsm_test));

    fsm_test.state = STATE_ALARM;
    TEST_ASSERT_EQUAL(STATE_ALARM, FSM_GetState(&fsm_test));
}