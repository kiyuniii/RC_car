#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define NRF_CE_PIN  7
#define NRF_CSN_PIN 8

#define MCP_CS_PIN 10

RF24 radio(NRF_CE_PIN, NRF_CSN_PIN); 
const byte address[6] = "12345";

void setup() {
  Serial.begin(115200);
  
  radio.begin();
  radio.openReadingPipe(0, address); 
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();         
}

void loop() {
  const char data[11] = "";
  
  if(radio.available()) {
    radio.read((void*)&data, sizeof(data));
    //radio.read(&data, sizeof(data));
  
    Serial.print("DATA RECEIVED: ");
    Serial.println(data);  
  }
  delay(50);
}
