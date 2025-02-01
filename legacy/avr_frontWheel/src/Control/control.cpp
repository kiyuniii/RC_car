#include "control.h"

Control::Control(int Xpin, int Ypin, uint8_t Lpin, uint8_t Rpin)
    : m_Xpin(Xpin), m_Ypin(Ypin), m_Lpin(Lpin), m_Rpin(Rpin)
{ 
    init();
}

Control::~Control()
{ 
    delete m_joyStick;
    delete m_Lmotor;
    delete m_Rmotor;
}

void Control::init() {
    m_joyStick = new JoyStick(m_Xpin, m_Ypin);
    m_Lmotor = new Motor(m_Lpin);
    m_Rmotor = new Motor(m_Rpin);

    #if DEBUG
        Serial.println("Control: INITIALIZED");    //UART
    #endif
}

void Control::update_control() {
    int xValue = analogRead(m_Xpin);
    int yValue = analogRead(m_Ypin);

    /* Deadzone */
    if(m_joyStick->calculate_angle(xValue, yValue) == -1) {
        m_Lmotor->run(RELEASE);
        m_Rmotor->run(RELEASE);
        return;
    }

    float angle = m_joyStick->calculate_angle(xValue, yValue);
    float speed = m_joyStick->calculate_speed(xValue, yValue);

   // 각도에 따른 동작 결정
    if (angle >= 45 && angle < 135) { // 좌회전
        turn_left(speed);
    } else if (angle >= 225 && angle < 315) { // 우회전
        turn_right(speed);
    } else if ((angle >= 0 && angle < 45) || (angle >= 315 && angle < 360)) { // 후진
        move_backward(speed);
    } else if (angle >= 135 && angle < 225) { // 전진
        move_forward(speed);
    } else {
        stop(); // 기타 경우에는 정지
    }
}

void Control::move_forward(int speed) {
    m_Lmotor->set_speed(speed);
    m_Rmotor->set_speed(speed);
    m_Lmotor->run(FORWARD);
    m_Rmotor->run(FORWARD);
}

void Control::move_backward(int speed) {
    m_Lmotor->set_speed(speed);
    m_Rmotor->set_speed(speed);
    m_Lmotor->run(BACKWARD);
    m_Rmotor->run(BACKWARD);
}

void Control::stop() {
    m_Lmotor->run(RELEASE);
    m_Rmotor->run(RELEASE);
}

void Control::turn_left(int speed) {
    m_Lmotor->set_speed(speed - 50); // 좌측 모터 속도를 줄임
    m_Rmotor->set_speed(speed);      // 우측 모터는 정상 속도
    m_Lmotor->run(FORWARD);          // 좌측 모터 후진
    m_Rmotor->run(FORWARD);          // 우측 모터 전진
}

void Control::turn_right(int speed) {
    m_Lmotor->set_speed(speed);       // 좌측 모터는 정상 속도
    m_Rmotor->set_speed(speed - 50);  // 우측 모터 속도를 줄임
    m_Lmotor->run(FORWARD);           // 좌측 모터 전진
    m_Rmotor->run(FORWARD);           // 우측 모터 후진
}