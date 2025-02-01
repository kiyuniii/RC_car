#include <AFMotor.h>
#include <mcp_can.h>
#include <SPI.h>

#define CAN0_INT 2 // D2
MCP_CAN CAN0(10); // CS = 10

#define SPEED  200
AF_DCMotor L_Motor(3);
AF_DCMotor R_Motor(4);

#define MODE_FORWARD  1
#define MODE_BACKWARD 2
#define MODE_LEFT     3
#define MODE_RIGHT    4
#define MODE_STOP     5

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

void setup() {
  Serial.begin(115200);
  SPI.begin();

  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) {
    Serial.println("[DONE] MCP2515 Initialized");
  } else {
    Serial.println("[FAIL] MCP2515 Initialized");
    // while (1);
  }

  CAN0.setMode(MCP_NORMAL); 
  pinMode(CAN0_INT, INPUT);

  L_Motor.setSpeed(SPEED);
  R_Motor.setSpeed(SPEED);
}

void loop() {
  int xValue = 0, yValue = 0;
  uint8_t opMode;

  // ✅ RX 메시지 확인
  if (CAN0.checkReceive() == CAN_MSGAVAIL) { 
    CAN0.readMsgBuf(&rxId, &len, rxBuf); 

    // RX ID 값이 유효한지 확인 (0x000 ~ 0x7FF)
    if (rxId > 0x7FF) {
      Serial.println("[ERROR] Invalid CAN ID Received");
      return;
    }

    Serial.print("CAN RECEIVED: RXID: ");
    Serial.print(rxId, HEX);

    if(rxId == 0x100) {   
      xValue = (rxBuf[0] << 8) | rxBuf[1];
      yValue = (rxBuf[2] << 8) | rxBuf[3];
      opMode = rxBuf[4];
    }

    Serial.print(" X: "); Serial.print(xValue);
    Serial.print(" Y: "); Serial.print(yValue);
    Serial.print(" MODE: "); Serial.print(opMode);

    handleVehicleMode(opMode, SPEED);

    // // ✅ CAN 데이터 송신 (버퍼 상태 확인 후 재시도)
    // uint8_t sndStat = CAN0.sendMsgBuf(0x100, 0, 5, rxBuf);
    // if (sndStat == CAN_OK) {
    //     Serial.println("[DONE] CAN : TX ====> FRONT");
    // } else {
    //     Serial.print("[FAIL] CAN : TX ==/=> FRONT, ERROR CODE: ");
    //     Serial.println(sndStat, HEX);
        
    //     // 송신 실패 시 CAN 모드 확인 후 재시도
    //     CAN0.setMode(MCP_NORMAL);
    //     delay(10);
    //     sndStat = CAN0.sendMsgBuf(0x100, 0, 5, rxBuf);
    //     if (sndStat == CAN_OK) {
    //         Serial.println("[O]");
    //     } else {
    //         Serial.print("[X]:");
    //         Serial.print(sndStat, HEX);
    //     }
    // }
  }
}

void move_forward(int value) {
  L_Motor.setSpeed(value);
  R_Motor.setSpeed(value);
  L_Motor.run(FORWARD);
  R_Motor.run(FORWARD);
}
void move_backward(int value) {
  L_Motor.setSpeed(value);
  R_Motor.setSpeed(value);
  L_Motor.run(BACKWARD);
  R_Motor.run(BACKWARD);
}
void stop() {
  L_Motor.run(RELEASE);
  R_Motor.run(RELEASE);
}
void turn_left(int value) {
  L_Motor.run(RELEASE);
  R_Motor.setSpeed(value);
  R_Motor.run(FORWARD);
}
void turn_right(int value) {
  L_Motor.setSpeed(value);
  L_Motor.run(FORWARD);
  R_Motor.run(RELEASE);
}

void handleVehicleMode(uint8_t mode, int speed) {
    switch (mode) {
        case MODE_FORWARD:
            Serial.println("|===== FORWARD ======|");
            move_forward(speed);
            break;
        case MODE_BACKWARD:
            Serial.println("|===== BACKWARD =====|");
            move_backward(speed);
            break;
        case MODE_LEFT:
            Serial.println("|==== TURN_LEFT =====|");
            turn_left(speed);
            break;
        case MODE_RIGHT:
            Serial.println("|==== TURN_RIGHT ====|");
            turn_right(speed);
            break;
        default:
            Serial.println("|======= STOP =======|");
            stop();
            break;
    }
}