#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"



//int msg[1];
//int done;
RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
int LED1 = 13;
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
//int LED1 = 13;
const int min_payload_size = 3;
const int max_payload_size = 32;
const int payload_size_increments_by = 2;
int next_payload_size = min_payload_size;


void setup(void){
  Serial.begin(57600);
  //printf_begin();
  radio.begin();
  radio.enableDynamicPayloads();
  radio.setRetries(15,15);
  //radio.setPayloadSize(8);
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening();
  radio.printDetails();
  
}

void loop(void){
  if ( radio.available() )
    {
      // Dump the payloads until we've gotten everything
      uint8_t len;
      bool done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
	len = radio.getDynamicPayloadSize();
	done = radio.read( receive_payload, len );

	// Put a zero at the end for easy printing
	receive_payload[len] = 0;

	// Spew it
	printf("Got payload size=%i value=%s\n\r",len,receive_payload);
        Serial.println(len);
        Serial.println(receive_payload[0]);
      }

      // First, stop listening so we can talk
      radio.stopListening();
   

      // Now, resume listening so we catch the next packets.
      radio.startListening();
    }
}

