#include <QTRSensors.h>
#include "Configuration.h"

QTRSensors qtr;
uint16_t sensorValues[SENSOR_COUNT];

void setup() {
  Serial.begin(9600);
  setupMotors();
  qtr.setTypeRC();
  qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, 11, 12, 13, 1}, SENSOR_COUNT);

  Serial.println("Starting Calibration... Place robot on line.");
  for (uint16_t i = 0; i < 400; i++) {
    digitalWrite(MOTOR_L_IN1, LOW);
    digitalWrite(MOTOR_L_IN2, HIGH);
    analogWrite(MOTOR_L_PWM, CALIBRATION_SPEED);
    digitalWrite(MOTOR_R_IN1, HIGH);
    digitalWrite(MOTOR_R_IN2, LOW);
    analogWrite(MOTOR_R_PWM, CALIBRATION_SPEED);
    qtr.calibrate();
  }
  analogWrite(MOTOR_L_PWM, 0);
  analogWrite(MOTOR_R_PWM, 0);
  Serial.println("Calibration Complete.");
}

void loop() {
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
  digitalWrite(MOTOR_STBY, HIGH);
}
