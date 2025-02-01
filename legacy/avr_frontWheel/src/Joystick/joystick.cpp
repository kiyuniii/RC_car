#include "joystick.h"
#include <math.h>

JoyStick::JoyStick(int Xpin, int Ypin) 
    : m_Xpin(Xpin), m_Ypin(Ypin)
{
    init();
}

JoyStick::~JoyStick() 
{ }

void JoyStick::init() {
    // pinMode(m_Xpin, INPUT_PULLUP);
    // pinMode(m_Ypin, INPUT_PULLUP);
    pinMode(m_Xpin, INPUT);
    pinMode(m_Ypin, INPUT);

    #if DEBUG
        Serial.println("JOYSTICK: INITIALIZED");    //UART
    #endif
}

float JoyStick::calculate_angle(int x, int y) {
    //Deadzone Settings
    if((abs(x - JOYSTICK_CENTER_X) < JOYSTICK_DEADZONE) && (abs(y - JOYSTICK_CENTER_Y) < JOYSTICK_DEADZONE)) {
        #if DEBUG
            printf("JOYSTICK: Deadzone status\n");
        #endif
        return -1;  //Deadzone, 모터 정지
    }

    float dx = x - JOYSTICK_CENTER_X;
    float dy = y - JOYSTICK_CENTER_Y;
    float angle = atan2(dy, dx) * 180 / M_PI;   //radian -> angle
    
    if(angle < 0) {
        angle += 360;
    }

    return angle;
}

int JoyStick::calculate_speed(int x, int y) {
    float dx = x - JOYSTICK_CENTER_X;
    float dy = y - JOYSTICK_CENTER_Y;
    float distance = sqrt(dx * dx + dy * dy);

    // 비선형 계산 (거리의 제곱 비례)
    float normalized_distance = constrain(distance / 512.0, 0, 1); // 0~1로 정규화
    float speed = constrain(pow(normalized_distance, 1.5) * 255, 0, 255); // 비선형 적용

    return (int)speed;
}
