#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
//#include "printf.h" 



//int msg[1];
//int done;
RF24 radio(9,10);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
//int LED1 = 13;
const int min_payload_size = 3;
const int max_payload_size = 32;
const int payload_size_increments_by = 2;
int next_payload_size = min_payload_size;

unsigned int receive_payload[max_payload_size+1]; // +1 to allow room for a terminating NULL char

void setup(void){
  Serial.begin(57600);
  //printf_begin();
  radio.begin();
  radio.enableDynamicPayloads();
  radio.setRetries(15,15);
  radio.enableAckPayload();
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening();
  radio.printDetails();
  
}

void loop(void){
  uint8_t len;
  static uint32_t message_count = 0;
  
  if ( radio.available() )
    {
      // Dump the payloads until we've gotten everything
      bool done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
	len = radio.getDynamicPayloadSize();
	done = radio.read(receive_payload, len );
        radio.writeAckPayload( 1, &message_count, sizeof(message_count) );
          ++message_count;
      Serial.println(message_count);
	// Put a zero at the end for easy printing
	receive_payload[len] = 0;

	// Spew it
	//printf("Got payload size=%i value=%s\n\r",len,receive_payload);
        Serial.println(len);
        Serial.println(receive_payload[0]);
        
     }
     //sets it to listen every 3 seconds for the transmitter is transmitting every 2 seconds
     delay(3000);
    }
    else{Serial.println("Nothing");}
}


