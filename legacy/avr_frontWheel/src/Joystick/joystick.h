#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#define JOYSTICK_CENTER_X 512   //조이스틱 중앙 값(X) (0 ~ 1023)
#define JOYSTICK_CENTER_Y 516   //조이스틱 중앙 값(Y) (0 ~ 1023)   
#define JOYSTICK_DEADZONE 20    //중앙의 약간의 움직임은 무시

#include "common/common.h"
#include "common/config.h"

class JoyStick {
public:
    JoyStick(int Xpin, int Ypin);
    ~JoyStick();
    void init();

    float calculate_angle(int x, int y);    //angle
    int calculate_speed(int x, int y);      //speed

private:
    int m_Xpin;
    int m_Ypin;
};

#endif//__JOYSTICK_H__