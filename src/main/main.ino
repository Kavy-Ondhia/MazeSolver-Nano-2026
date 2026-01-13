#include <QTRSensors.h>
#include "Configuration.h"

QTRSensors qtr;
uint16_t sensorValues[SENSOR_COUNT];

void setup() {
  Serial.begin(9600);
  
  // 1. Initialize Motors
  setupMotors();
  
  // 2. Initialize Encoders
  setupEncoders();
  
  // 3. Initialize Sensors
  qtr.setTypeRC();
  // Uses the mapping from Configuration.h
  const uint8_t pins[] = SENSOR_PINS;
  qtr.setSensorPins(pins, SENSOR_COUNT);
  
  // 4. Calibration Sequence
  Serial.println("Starting Calibration... Robot will spin.");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  for (uint16_t i = 0; i < 400; i++) {
    // Spin in place
    digitalWrite(MOTOR_L_IN1, LOW);
    digitalWrite(MOTOR_L_IN2, HIGH);
    analogWrite(MOTOR_L_PWM, CALIBRATION_SPEED);

    digitalWrite(MOTOR_R_IN1, HIGH);
    digitalWrite(MOTOR_R_IN2, LOW);
    analogWrite(MOTOR_R_PWM, CALIBRATION_SPEED);

    qtr.calibrate(); 
  }

  // Stop motors
  analogWrite(MOTOR_L_PWM, 0);
  analogWrite(MOTOR_R_PWM, 0);
  digitalWrite(LED_BUILTIN, LOW);
  
  Serial.println("Calibration Complete.");
}

void loop() {
  // Read calibrated sensor data
  qtr.readCalibrated(sensorValues); 
  
  // Print values (0 to 1000) to Serial Monitor
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
  
  digitalWrite(MOTOR_STBY, HIGH); 
}

void setupEncoders() {
  pinMode(ENCODER_L_A, INPUT);
  pinMode(ENCODER_L_B, INPUT);
  pinMode(ENCODER_R_A, INPUT);
  pinMode(ENCODER_R_B, INPUT);
}