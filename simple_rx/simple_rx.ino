#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <mcp_can.h>

#define NRF_CE_PIN  7                     
#define NRF_CSN_PIN 8   //ACTIVE-LOW
#define CAN_CS_PIN  10  //ACTIVE-LOW

#define MODE_FORWARD  1
#define MODE_BACKWARD 2
#define MODE_LEFT     3
#define MODE_RIGHT    4
#define MODE_STOP     5

RF24 radio(NRF_CE_PIN, NRF_CSN_PIN); 
MCP_CAN CAN0(CAN_CS_PIN);               //#define MCP_CS_PIN 10
const byte address[6] = "23122";

void setup() {
  Serial.begin(115200);
  
  SPI.begin();    //

  /* [MCP2515] CAN INIT */
  digitalWrite(NRF_CSN_PIN, HIGH);      //NRF_CSN OFF
  digitalWrite(CAN_CS_PIN, LOW);        //CAN_CS  ON
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ) == CAN_OK) {  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
    Serial.println("[DONE] MCP2515 INIT");
  } else {
    Serial.println("[FAIL] MCP2515 INIT");
  }
  CAN0.setMode(MCP_NORMAL); // Change to normal mode to allow messages to be transmitted
  delay(100);
  /* [NRF24L01] RF INIT */
  digitalWrite(CAN_CS_PIN, HIGH);   //CAN_CS  OFF
  digitalWrite(NRF_CSN_PIN, LOW);   //NRF_CSN ON
  radio.begin();
  radio.openReadingPipe(0, address); 
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  /* [NRF] DATA RECEIVE */
  digitalWrite(CAN_CS_PIN, HIGH);   //CAN_CS  OFF
  digitalWrite(NRF_CSN_PIN, LOW);   //NRF_CSN ON
  char data[11];
  memset(data, 0, sizeof(data));
  if(radio.available()) {
    radio.read((void*)data, sizeof(data));
    Serial.print("DATA RECEIVED: ");
    Serial.print(data);
  }
  digitalWrite(NRF_CSN_PIN, HIGH);  //NRF_CSN OFF

  //PARSING DATA(char -> int)
  int xValue, yValue, zValue;
  sscanf(data, "%4d%4d%2d", &xValue, &yValue, &zValue); 
  char buffer[30];
  sprintf(buffer, " | X:%04d Y:%04d Z:%02d", xValue, yValue, zValue);
  Serial.print(buffer);

  //DETERMINE VEHICLE MODE
  uint8_t opMode;
  if(       xValue >= 0 && xValue <= 460 
       && yValue >= 460 && yValue <= 560) {
      opMode = MODE_RIGHT;
        }
  else if(xValue >= 560 && xValue <= 1023 
       && yValue >= 460 && yValue <= 560) {
      opMode = MODE_LEFT;
  }
  else if(xValue >= 460 && xValue <= 560 
       && yValue >= 560 && yValue <= 1023) {
      opMode = MODE_BACKWARD;
  }
  else if(xValue >= 460 && xValue <= 560 
         && yValue >= 0 && yValue <= 460) {
      opMode = MODE_FORWARD;
  }
  else {
      opMode = MODE_STOP;
  }
  
  switch(opMode) {
    case MODE_FORWARD:
      Serial.print("|===== FORWARD ======|");
      break;
    case MODE_BACKWARD:
      Serial.print("|===== BACKWARD =====|");
      break;
    case MODE_LEFT:
      Serial.print("|==== TURN_LEFT =====|");
      break;
    case MODE_RIGHT:
      Serial.print("|==== TURN_RIGHT ====|");
      break;
    default:
      Serial.print("|======= STOP =======|");
      break;
  }

  //BUILD CAN_DATA (xValue:2Byte, yValue:2Byte, MODE:1Byte)
  uint8_t canData[5] = {0};
  canData[0] = (xValue >> 8) & 0xFF;  //xValue_MSB
  canData[1] = xValue & 0xFF;         //xValue_LSB
  canData[2] = (yValue >> 8) & 0xFF;  //yValue_MSB
  canData[3] = yValue & 0xFF;         //yValue_LSB
  canData[4] = opMode;                //Operation Mode

  /* [CAN] DATA TRANSMIT */
  digitalWrite(NRF_CSN_PIN, HIGH);    //NRF_CSN OFF
  digitalWrite(CAN_CS_PIN, LOW);      //CAN_CS  ON
  uint8_t sndStat = CAN0.sendMsgBuf(0x100, 0, 5, canData);  //Rx = 0x88
  if(sndStat == CAN_OK){
    Serial.println("[DONE] CAN : RX ====> FRONT");
  } else {
    Serial.println("[FAIL] CAN : RX ==/=> FRONT");
  }
  delay(10);
  digitalWrite(CAN_CS_PIN, HIGH);     //CAN_CS  OFF

  delay(50);
}

