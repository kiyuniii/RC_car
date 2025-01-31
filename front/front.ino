#include <SoftwareSerial.h>
#include <AFMotor.h>

// #define L_MOTOR_PIN 3
// #define R_MOTOR_PIN 4
#define SPEED  200

AF_DCMotor L_Motor(3);
AF_DCMotor R_Motor(4);

void setup() {
  Serial.begin(115200);
  L_Motor.setSpeed(SPEED);
  R_Motor.setSpeed(SPEED);
}

void loop() {
  move_forward(SPEED);
  delay(1000);
  stop();
  delay(500);

  move_backward(SPEED);
  delay(1000);
  stop();
  delay(500);

  turn_left(SPEED);
  delay(1000);
  stop();
  delay(500);

  turn_right(SPEED);
  delay(1000);
  stop();
  delay(500);
}


void move_forward(int value) {
  Serial.println("MOVE FORWARD");
  L_Motor.setSpeed(value);
  R_Motor.setSpeed(value);
  L_Motor.run(FORWARD);
  R_Motor.run(FORWARD);
}

void move_backward(int value) {
  Serial.println("MOVE BACKWARD");
  L_Motor.setSpeed(value);
  R_Motor.setSpeed(value);
  L_Motor.run(BACKWARD);
  R_Motor.run(BACKWARD);
}

void stop() {
  Serial.println("STOP");
  L_Motor.run(RELEASE);
  R_Motor.run(RELEASE);
}

void turn_left(int value) {
  Serial.println("TURN_LEFT");
  L_Motor.run(RELEASE);
  R_Motor.setSpeed(value);
  R_Motor.run(FORWARD);
}

void turn_right(int value) {
  Serial.println("TURN_RIGHT");
  L_Motor.setSpeed(value);
  L_Motor.run(FORWARD);
  R_Motor.run(RELEASE);
}