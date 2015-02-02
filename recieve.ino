#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
 



int msg[1];
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int LED1 = 13;


void setup(void){
  Serial.begin(9600);
  radio.begin();
  radio.setRetries(15,15);
  radio.setPayloadSize(8);
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  pinMode(LED1, OUTPUT);
  
}

void loop(void){
  
  if (radio.available()){
    bool done = false;    
    while (!done){
      done = radio.read(msg, 1);      
   Serial.println(msg[0]);
      delay(100);
    }
  }
  else
  {Serial.println("No radio available");}
}

