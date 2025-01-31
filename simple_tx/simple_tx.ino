#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN  7       //NRF24L01
#define CSN_PIN 8       //NRF24L01
#define X_PIN A0        //JOYSTICK    
#define Y_PIN A1        //JOYSTICK
#define Z_PIN A2        //JOYSTICK

RF24 radio(CE_PIN, CSN_PIN); 
const byte address[6] = "12345";

void setup() {
  pinMode(X_PIN, INPUT);
  pinMode(Y_PIN, INPUT);
  pinMode(Z_PIN, INPUT);

  Serial.begin(115200);
  
  radio.begin();
  radio.openWritingPipe(address); //이전에 설정한 5글자 문자열인 데이터를 보낼 수신의 주소를 설정
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();          //모듈을 송신기로 설정
}

void loop() {
  int xValue = analogRead(A1);
  int yValue = analogRead(A0);
  int zValue = analogRead(A2);
  if(zValue != 0) zValue = 1;

  char serial_buffer[50];  // 출력 문자열을 저장할 버퍼
  char data_buffer[50];    // 송신 문자열을 저장할 버퍼
  sprintf(serial_buffer, "X: %4d  Y: %4d  Z: %d", xValue, yValue, zValue);
  sprintf(data_buffer, "%04d%04d%02d", xValue, yValue, zValue);
  Serial.print(serial_buffer);
  Serial.print("      DATA: ");
  Serial.print(data_buffer);

  uint8_t data[11];  // 10자리 숫자 + 널 문자(\0)
  sprintf((char*)data, "%04d%04d%02d", xValue, yValue, zValue);

  bool tx_result = radio.write(&data, sizeof(data));
  if(tx_result) {
    Serial.println("      MESSAGE SENT SUCCESSFULLY!");
  } else {
    Serial.println("      MESSAGE FAILED!");
  }
  delay(50);
}
