#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "common/common.h"
#include "common/config.h"
#include "Motor/motor.h"
#include "Joystick/joystick.h"

class Control {
public:
    Control(int Xpin, int Ypin, uint8_t Lpin, uint8_t Rpin);
    ~Control();

    void init();

    void update_control();
    void move_forward(int speed);
    void move_backward(int speed);
    void stop();
    void turn_left(int speed);
    void turn_right(int speed);

    uint8_t get_pwmfreq(uint8_t pwmfreq);

private:
    Motor *m_Lmotor;
    Motor *m_Rmotor;
    JoyStick *m_joyStick;
    
    int m_Xpin, m_Ypin;
    uint8_t m_Lpin, m_Rpin;
    //uint8_t m_pwmfreq;
};

#endif//__CONTROL_H__