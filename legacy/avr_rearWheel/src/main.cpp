#include "common/common.h"
#include "common/pin.h"
#include "Control/control.h"

Control *control;
// AF_DCMotor motor1(3);
// AF_DCMotor motor2(4);
void setup() {
    Serial.begin(115200);

    control = new Control(JOYSTICK_PIN_X, JOYSTICK_PIN_Y, MOTOR_PIN_L, MOTOR_PIN_R);
    delay(1000);
    Serial.println("MAIN: INITIALIZED");
    delay(100);
    // motor1.setSpeed(70);
    // motor2.setSpeed(70);
    // motor1.run(RELEASE);
    // motor2.run(RELEASE);
}


void loop() {
    control->update_control();
    /* motor1.run(FORWARD);
    delay(1000);
    motor1.run(BACKWARD);
    delay(1000);
    motor2.run(FORWARD);
    delay(1000);
    motor2.run(BACKWARD);
    delay(1000); */
}
