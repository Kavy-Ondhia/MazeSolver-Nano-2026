#include <QTRSensors.h>
#include "Configuration.h"

QTRSensors qtr;
uint16_t sensorValues[SENSOR_COUNT];

// PID Variables
int lastError = 0;
int baseSpeed = 120; // Start slower for the prototype
int maxSpeed = 200;  // Limit power to protect the DRV8833

void setup() {
  Serial.begin(9600);
  
  // 1. Initialize Hardware
  setupMotors();
  setupEncoders();
  
  // 2. Initialize Sensors (A0-A5, D6, D13)
  qtr.setTypeRC();
  const uint8_t pins[] = SENSOR_PINS; 
  qtr.setSensorPins(pins, SENSOR_COUNT);
  
  // 3. Calibration (Robot spins to "see" the line)
  calibrateRobot();
  
  Serial.println("Ready to follow line!");
}

void loop() {
  // 1. Get position (0 to 7000)
  uint16_t position = qtr.readLineBlack(sensorValues);

  // 2. Safety Check: If robot is completely off the line
  // If all middle sensors see white, use last known error to find the line
  if (sensorValues[2] < 150 && sensorValues[3] < 150 && sensorValues[4] < 150 && sensorValues[5] < 150) {
    if (lastError > 0) driveMotors(baseSpeed, -baseSpeed); // Sharp right recovery
    else driveMotors(-baseSpeed, baseSpeed);              // Sharp left recovery
    return;
  }

  // 3. PID Calculation
  int error = (int)position - 3500;
  
  // Standard PID formula
  int correction = (Kp * error) + (Kd * (error - lastError));
  lastError = error;

  // 4. Calculate Motor Speeds
  int leftMotorSpeed = baseSpeed + correction;
  int rightMotorSpeed = baseSpeed - correction;

  // 5. Constrain speeds to PWM limits (0-255)
  leftMotorSpeed = constrain(leftMotorSpeed, -maxSpeed, maxSpeed);
  rightMotorSpeed = constrain(rightMotorSpeed, -maxSpeed, maxSpeed);

  // 6. Execution
  driveMotors(leftMotorSpeed, rightMotorSpeed);
}

// --- HARDWARE CONTROL FUNCTIONS ---

void driveMotors(int left, int right) {
  // LEFT MOTOR: DRV8833 Logic
  if (left >= 0) {
    analogWrite(MOTOR_L_IN1, left);
    digitalWrite(MOTOR_L_IN2, LOW);
  } else {
    digitalWrite(MOTOR_L_IN1, LOW);
    analogWrite(MOTOR_L_IN2, abs(left));
  }

  // RIGHT MOTOR: DRV8833 Logic
  if (right >= 0) {
    analogWrite(MOTOR_R_IN1, right);
    digitalWrite(MOTOR_R_IN2, LOW);
  } else {
    digitalWrite(MOTOR_R_IN1, LOW);
    analogWrite(MOTOR_R_IN2, abs(right));
  }
}

void calibrateRobot() {
  Serial.println("Calibrating... Spinning...");
  digitalWrite(LED_BUILTIN, HIGH);

  for (uint16_t i = 0; i < 200; i++) {
    // Slowly spin in place to pass sensors over the line
    driveMotors(100, -100); 
    qtr.calibrate();
    delay(10);
  }
  
  driveMotors(0, 0); 
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Calibration Done.");
}

void setupMotors() {
  pinMode(MOTOR_L_IN1, OUTPUT);
  pinMode(MOTOR_L_IN2, OUTPUT);
  pinMode(MOTOR_R_IN1, OUTPUT);
  pinMode(MOTOR_R_IN2, OUTPUT);
  // DRV8833 Sleep/Enable pin if you have one connected
  // pinMode(MOTOR_STBY, OUTPUT);
  // digitalWrite(MOTOR_STBY, HIGH);
}

void setupEncoders() {
  pinMode(ENCODER_L_A, INPUT);
  pinMode(ENCODER_L_B, INPUT);
  pinMode(ENCODER_R_A, INPUT);
  pinMode(ENCODER_R_B, INPUT);
}