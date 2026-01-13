#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// --- MOTOR PINS ---
#define MOTOR_L_PWM 9
#define MOTOR_L_IN1 7
#define MOTOR_L_IN2 8

#define MOTOR_R_PWM 10
#define MOTOR_R_IN1 4
#define MOTOR_R_IN2 5

#define MOTOR_STBY 6 // Tied to 5V or D6 depending on Karunya's final trace

// --- ENCODER PINS ---
#define ENCODER_L_A 2   // Interrupt
#define ENCODER_L_B 11  // Direction
#define ENCODER_R_A 3   // Interrupt
#define ENCODER_R_B 12  // Direction

// --- SENSOR SETTINGS ---
#define SENSOR_COUNT 8
// Pins based on your table: A0, A1, A2, A3, D6, A4, A5, D13
#define SENSOR_PINS {A0, A1, A2, A3, 6, A4, A5, 13}
#define CALIBRATION_SPEED 100 

// --- PID CONSTANTS ---
float Kp = 0.5;
float Kd = 1.0;
float Ki = 0.0;

#endif