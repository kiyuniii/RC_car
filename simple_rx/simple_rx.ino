#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN  7
#define CSN_PIN 8

RF24 radio(CE_PIN, CSN_PIN); 
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
  radio.read(&data, sizeof(data));
  Serial.print("DATA RECEIVED: ");
  Serial.println(data);
  delay(1000);
}
