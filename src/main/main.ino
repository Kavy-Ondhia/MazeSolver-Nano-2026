#include <QTRSensors.h>
#include "Configuration.h"

QTRSensors qtr;
uint16_t sensorValues[SENSOR_COUNT];

void setup() {
  Serial.begin(9600);
  
  // 1. Initialize Motors
  setupMotors();
  
  // 2. Initialize Sensors
  qtr.setTypeRC();
  // Ensure these pins match your physical wiring tonight!
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, 11, 12, 13, 1}, SENSOR_COUNT);

  // 3. Sensor-Motor Synchronization (Calibration)
  // This makes the robot spin in place to 'see' the line and the floor
  Serial.println("Starting Calibration... Place robot on line.");
  
  for (uint16_t i = 0; i < 400; i++) {
    // Spin robot slowly to the left
    digitalWrite(MOTOR_L_IN1, LOW);
    digitalWrite(MOTOR_L_IN2, HIGH);
    analogWrite(MOTOR_L_PWM, CALIBRATION_SPEED);

    digitalWrite(MOTOR_R_IN1, HIGH);
    digitalWrite(MOTOR_R_IN2, LOW);
    analogWrite(MOTOR_R_PWM, CALIBRATION_SPEED);

    qtr.calibrate(); // Record sensor min/max values
  }

  // Stop motors after calibration
  analogWrite(MOTOR_L_PWM, 0);
  analogWrite(MOTOR_R_PWM, 0);
  Serial.println("Calibration Complete.");
}

void loop() {
  // Tonight, we will use this to print sensor data to verify the sync
  qtr.readCalibrated(sensorValues); 
  
  for (uint8_t i = 0; i < SENSOR_COUNT; i++) {
    Serial.print(sensorValues[i]);
    Serial.print("\t");
  }
  Serial.println();
  delay(100);
}

void setupMotors() {
  pinMode(MOTOR_L_PWM, OUTPUT);
  pinMode(MOTOR_L_IN1, OUTPUT);
  pinMode(MOTOR_L_IN2, OUTPUT);
  pinMode(MOTOR_R_PWM, OUTPUT);
  pinMode(MOTOR_R_IN1, OUTPUT);
  pinMode(MOTOR_R_IN2, OUTPUT);
  pinMode(MOTOR_STBY, OUTPUT);
  
  digitalWrite(MOTOR_STBY, HIGH); // Wake up the motor driver
}