#include <QTRSensors.h>
#include "Configuration.h"

QTRSensors qtr;
uint16_t sensorValues[SENSOR_COUNT];

// PID Variables
int lastError = 0;
int baseSpeed = 150; // Cruising speed (Adjust this first)
int maxSpeed = 255;  // Max PWM limit

void setup() {
  Serial.begin(9600);
  
  // 1. Initialize Hardware
  setupMotors();
  setupEncoders();
  
  // 2. Initialize Sensors
  qtr.setTypeRC();
  const uint8_t pins[] = SENSOR_PINS;
  qtr.setSensorPins(pins, SENSOR_COUNT);
  
  // 3. Calibration Dance (Spins in place)
  calibrateRobot();
}

void loop() {
  // 1. Get position (0 to 7000)
  // readLineBlack handles the weighted average for us
  uint16_t position = qtr.readLineBlack(sensorValues);

  // 2. Calculate Error (3500 is the center)
  int error = (int)position - 3500;

  // 3. PID Calculation
  // motorSpeed is the "correction" value
  int motorSpeed = (Kp * error) + (Kd * (error - lastError));
  lastError = error;

  // 4. Set Individual Motor Speeds
  int leftMotorSpeed = baseSpeed + motorSpeed;
  int rightMotorSpeed = baseSpeed - motorSpeed;

  // 5. Check for Maze Intersections (LSRB Logic Pre-work)
  // If all sensors see white (Dead End)
  if (position == 0 && sensorValues[0] < 100 && sensorValues[7] < 100) {
      // Robot lost the line or hit a dead end
      // For now, let's spin to find the line again
      driveMotors(-80, 80); 
  } 
  // If all sensors see black (Cross-section / T-Junction)
  else if (sensorValues[0] > 800 && sensorValues[7] > 800) {
      // Logic for Maze: Decision point
      // For now, keep going straight
      driveMotors(baseSpeed, baseSpeed);
  }
  // 6. Normal Line Following
  else {
      leftMotorSpeed = constrain(leftMotorSpeed, 0, maxSpeed);
      rightMotorSpeed = constrain(rightMotorSpeed, 0, maxSpeed);
      driveMotors(leftMotorSpeed, rightMotorSpeed);
  }
}

// --- HELPER FUNCTIONS ---

void driveMotors(int left, int right) {
  // Left Motor Direction
  if (left >= 0) {
    digitalWrite(MOTOR_L_IN1, HIGH);
    digitalWrite(MOTOR_L_IN2, LOW);
  } else {
    digitalWrite(MOTOR_L_IN1, LOW);
    digitalWrite(MOTOR_L_IN2, HIGH);
  }
  analogWrite(MOTOR_L_PWM, abs(left));

  // Right Motor Direction
  if (right >= 0) {
    digitalWrite(MOTOR_R_IN1, HIGH);
    digitalWrite(MOTOR_R_IN2, LOW);
  } else {
    digitalWrite(MOTOR_R_IN1, LOW);
    digitalWrite(MOTOR_R_IN2, HIGH);
  }
  analogWrite(MOTOR_R_PWM, abs(right));
}

void calibrateRobot() {
  Serial.println("Starting Calibration...");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  for (uint16_t i = 0; i < 400; i++) {
    driveMotors(-CALIBRATION_SPEED, CALIBRATION_SPEED); // Spin in place
    qtr.calibrate();
  }
  
  driveMotors(0, 0); // Stop
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Calibration Done.");
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