#ifndef __MOTOR_CONTROL_H__
#define __MOTOR_CONTROL_H__

#include "common/common.h"
#include "common/config.h"
#include <AFMotor.h>    //https://github.com/jms1234/Arduino/blob/master/libraries/AFMotor/AFMotor.h

class Motor {
public:
    Motor(uint8_t pin);
    ~Motor();

    void init();
    void run(uint8_t cmd);
    void set_speed(uint8_t speed);

private:
    AF_DCMotor *m_motor;
    uint8_t m_pin;
    uint8_t m_pwmfreq;
};

#endif//__MOTOR_CONTROL_H__