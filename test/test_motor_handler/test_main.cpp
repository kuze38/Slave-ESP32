#include <Arduino.h>
#include <unity.h>
#include "Motor_handler.h"
#include "Comms.h"

// Mock Definitions
#ifdef UNIT_TEST

// Mocked Pin States
int pin_states[40];  // Array to store states of pins (assuming max 40 GPIO pins)

// Define motor pins (mocked for unit tests)
#define MOTOR_A_PIN1 10
#define MOTOR_A_PIN2 11
#define MOTOR_B_PIN1 12
#define MOTOR_B_PIN2 13

// Mock LoRa functions
int mock_LoRa_parsePacket() {
    // Simulate a received packet
    return 1;  // Simulate a packet size of 1 byte
}

char mock_LoRa_read() {
    // Simulate receiving a command
    static int counter = 0;
    tMovement commands[] = {MOVEMENT_FORWARD, MOVEMENT_BACKWARD, MOVEMENT_RIGHT, MOVEMENT_LEFT};
    return commands[counter++ % 4];  // Rotate through commands
}

#define LoRa_parsePacket mock_LoRa_parsePacket
#define LoRa_read mock_LoRa_read

// Mock digitalWrite function
void mock_digitalWrite(int pin, int value) {
    if (pin >= 0 && pin < 40) {
        pin_states[pin] = value;  // Store pin state
    }
}

// Mock digitalRead function
int mock_digitalRead(int pin) {
    if (pin >= 0 && pin < 40) {
        return pin_states[pin];  // Return stored pin state
    }
    return LOW;  // Default to LOW
}

// Map to real functions for mocking
#define digitalWrite mock_digitalWrite
#define digitalRead mock_digitalRead

#endif

// Test cases
void test_handle_LoRa_command_forward() {
    // Initialize mock pin states
    memset(pin_states, LOW, sizeof(pin_states));  // Set all pins to LOW initially

    // Simulate receiving MOVEMENT_FORWARD command
    handle_LoRa_command();

    // Verify pin states for MOVEMENT_FORWARD
    TEST_ASSERT_EQUAL(HIGH, digitalRead(MOTOR_A_PIN1));
    TEST_ASSERT_EQUAL(LOW, digitalRead(MOTOR_A_PIN2));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(MOTOR_B_PIN1));
    TEST_ASSERT_EQUAL(LOW, digitalRead(MOTOR_B_PIN2));
}

void test_handle_LoRa_command_backward() {
    // Initialize mock pin states
    memset(pin_states, LOW, sizeof(pin_states));  // Set all pins to LOW initially

    // Simulate receiving MOVEMENT_BACKWARD command
    handle_LoRa_command();

    // Verify pin states for MOVEMENT_BACKWARD
    TEST_ASSERT_EQUAL(LOW, digitalRead(MOTOR_A_PIN1));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(MOTOR_A_PIN2));
    TEST_ASSERT_EQUAL(LOW, digitalRead(MOTOR_B_PIN1));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(MOTOR_B_PIN2));
}

void test_handle_LoRa_command_right() {
    // Initialize mock pin states
    memset(pin_states, LOW, sizeof(pin_states));  // Set all pins to LOW initially

    // Simulate receiving MOVEMENT_RIGHT command
    handle_LoRa_command();

    // Verify pin states for MOVEMENT_RIGHT
    TEST_ASSERT_EQUAL(HIGH, digitalRead(MOTOR_A_PIN1));
    TEST_ASSERT_EQUAL(LOW, digitalRead(MOTOR_A_PIN2));
    TEST_ASSERT_EQUAL(LOW, digitalRead(MOTOR_B_PIN1));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(MOTOR_B_PIN2));
}

void test_handle_LoRa_command_left() {
    // Initialize mock pin states
    memset(pin_states, LOW, sizeof(pin_states));  // Set all pins to LOW initially

    // Simulate receiving MOVEMENT_LEFT command
    handle_LoRa_command();

    // Verify pin states for MOVEMENT_LEFT
    TEST_ASSERT_EQUAL(LOW, digitalRead(MOTOR_A_PIN1));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(MOTOR_A_PIN2));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(MOTOR_B_PIN1));
    TEST_ASSERT_EQUAL(LOW, digitalRead(MOTOR_B_PIN2));
}

void setup() {
    // Initialize Unity test framework
    UNITY_BEGIN();

    // Run test cases
    RUN_TEST(test_handle_LoRa_command_forward);
    RUN_TEST(test_handle_LoRa_command_backward);
    RUN_TEST(test_handle_LoRa_command_right);
    RUN_TEST(test_handle_LoRa_command_left);

    UNITY_END();  // End test framework
}

void loop() {
    // Loop is not needed for testing
}
