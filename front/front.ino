#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <mcp_can.h>
#include <SPI.h>

// #define L_MOTOR_PIN 3
// #define R_MOTOR_PIN 4
#define CAN0_INT 2          //D2
MCP_CAN CAN0(10);           //#define MCP_CS_PIN 10

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
char msgString[128];

void setup() {
  Serial.begin(115200);

  /* [MCP2515] CAN INIT */
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) {
    Serial.println("[DONE] MCP2515 Initialized");
  } else {
    Serial.println("[FAIL] MCP2515 Initialized");
  }

  CAN0.setMode(MCP_NORMAL); // Change to normal mode to allow messages to be transmitted
  pinMode(CAN0_INT, INPUT);

  L_Motor.setSpeed(SPEED);
  R_Motor.setSpeed(SPEED);
}

void loop() {
  int xValue, yValue;
  uint8_t opMode;

  if(!digitalRead(CAN0_INT)) {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);

    if(rxId == 0x100) {     //CHECK WHETHER CAN_TX IS RF_RX
      xValue = (rxBuf[0] << 8) | rxBuf[1];
      yValue = (rxBuf[2] << 8) | rxBuf[3];
      opMode = rxBuf[4];
    }
    
    switch(opMode) {
      case MODE_FORWARD:
        Serial.println("==== FORWARD ====");
        move_forward(speed);
        break;
      case MODE_BACKWARD:
        Serial.println("==== BACKWARD ====");
        move_backward(speed);
        break;
      case MODE_LEFT:
        Serial.println("==== TURN_LEFT ====");
        turn_left(speed);
        break;
      case MODE_RIGHT:
        Serial.println("==== TURN_RIGHT ====");
        turn_right(speed);
        break;
    }

    //PRINT RECEIVED VALUES
    Serial.println("=== Received CAN Data ===");
    Serial.print("xValue: "); Serial.println(xValue);
    Serial.print("yValue: "); Serial.println(yValue);
    Serial.print("opMode: "); Serial.println(opMode);
    Serial.println("=====================");
  
    // // If you want to see raw bytes (optional)
    // Serial.print("Raw bytes: ");
    // for(byte i = 0; i < len; i++) {
    //   Serial.print("0x");
    //   Serial.print(rxBuf[i], HEX);
    //   Serial.print(" ");
    // }
    // Serial.println();
  }
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