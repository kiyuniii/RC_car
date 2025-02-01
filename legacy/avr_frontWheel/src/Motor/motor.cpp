#include "motor.h"

Motor::Motor(uint8_t pin)
    : m_pin(pin) 
{ 
    init(); 
}

Motor::~Motor() 
{   
    delete m_motor;
}

void Motor::init() {
    m_motor = new AF_DCMotor(m_pin);

    #if DEBUG
        Serial.println("MOTOR: INITIALIZED");
    #endif
}

void Motor::run(uint8_t cmd) {
    switch(cmd) {
        case FORWARD:
            m_motor->run(FORWARD);
            break;
        case BACKWARD:
            m_motor->run(BACKWARD);
            break;
        case RELEASE:
            m_motor->run(RELEASE);
            break;
        default:
            break;
    }
}

void Motor::set_speed(uint8_t speed) {
    m_motor->setSpeed(speed);
}
