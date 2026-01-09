#include <QTRSensors.h>
#include "Configuration.h"

QTRSensors qtr;
uint16_t sensorValues[SENSOR_COUNT];

void setup() {
  Serial.begin(9600);
  
  // 1. Initialize Motors (Pins defined in Configuration.h)
  setupMotors();
  
  // 2. Initialize Sensors
  qtr.setTypeRC();
  
  // Updated to match the photo mapping: D2, D4, D7, D8, D10, D11, D12, A0
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, SENSOR_COUNT);
  
  // 3. Sensor-Motor Synchronization (Calibration)
  Serial.println("Starting Calibration... Place robot on line.");
  
  // Build-in LED helps see when calibration is active
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  for (uint16_t i = 0; i < 400; i++) {
    // Spin robot slowly in place to 'see' the floor
    digitalWrite(MOTOR_L_IN1, LOW);
    digitalWrite(MOTOR_L_IN2, HIGH);
    analogWrite(MOTOR_L_PWM, CALIBRATION_SPEED);

    digitalWrite(MOTOR_R_IN1, HIGH);
    digitalWrite(MOTOR_R_IN2, LOW);
    analogWrite(MOTOR_R_PWM, CALIBRATION_SPEED);

    qtr.calibrate(); 
  }

  // Stop motors and turn off LED after calibration
  analogWrite(MOTOR_L_PWM, 0);
  analogWrite(MOTOR_R_PWM, 0);
  digitalWrite(LED_BUILTIN, LOW);
  
  Serial.println("Calibration Complete.");
}

void loop() {
  // Read sensor data and print to Serial Monitor for verification
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