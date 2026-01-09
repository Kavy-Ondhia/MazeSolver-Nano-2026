#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// --- MOTOR PINS ---
#define MOTOR_L_PWM 9
#define MOTOR_L_IN1 7
#define MOTOR_L_IN2 8

#define MOTOR_R_PWM 10
#define MOTOR_R_IN1 4
#define MOTOR_R_IN2 5

#define MOTOR_STBY 6

// --- ENCODER PINS ---
#define ENCODER_L_A 2
#define ENCODER_R_A 3

// --- SENSOR SETTINGS ---
#define SENSOR_COUNT 8
#define CALIBRATION_SPEED 100 

// --- PID CONSTANTS ---
float Kp = 0.5;
float Kd = 1.0;
float Ki = 0.0;

#endif