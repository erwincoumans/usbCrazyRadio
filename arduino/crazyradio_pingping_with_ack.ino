#include <SPI.h>
#include "RF24.h"
#include "printf.h"

//choose the CE pin (9 here) and CS pin (10 here)
RF24 radio(9,10);

// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xe7e7e7e7e7LL;//0xE8E8F0F0E1LL;


static uint32_t message_count = 1;

//for debugging
//#define USE_SERIAL

void setup()
{
#ifdef USE_SERIAL
  Serial.begin(115200);   // First open the serial connection via the USB
  while (!Serial) {}
  printf_begin();
  printf("Test printf OK.\n");
#endif

radio.begin();

  // We will be using the Ack Payload feature, so please enable it
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.writeAckPayload( 1, &message_count, sizeof(message_count) );
 
  radio.openReadingPipe(1,pipe);
  radio.startListening();

  //
  // Dump the configuration of the rf unit for debugging
  //
#ifdef USE_SERIAL
  radio.printDetails();
#endif//USE_SERIAL

}

int threshold = 3;

const int min_payload_size = 4;
const int max_payload_size = 32;
const int payload_size_increments_by = 2;
int next_payload_size = min_payload_size;

unsigned char receive_payload[max_payload_size+1]; // +1 to allow room for a terminating NULL char
unsigned long bla;

struct MyStatus
{
  int message_count;
  char potValueA;
  char potValueB;
  char unused1;
  char unused2;
  

};
void loop()
{
 

    // if there is data ready
    if ( radio.available() )
    {
     // printf("radio available\n");
      // Dump the payloads until we've gotten everything
      static unsigned long got_time;
      bool done = false;

      bool dynamicPayload = true;
      if (dynamicPayload)
      {
         while (!done)
        {
          // Fetch the payload, and see if this was the last one.
  	int len = radio.getDynamicPayloadSize();
  	done = radio.read( receive_payload, len );
  
  	// Put a zero at the end for easy printing
  	receive_payload[len] = 0;
  
      // Spew it
  #ifdef USE_SERIAL
  	printf("Got dynamic payload size=%d:\n\r",len);
        for (int i=0;i<len;i++)
        {
          int v = receive_payload[i];
          printf("value[%d]=%d\n",i,v);
        }
  #endif //USE_SERIAL
        }
      } else
      {
        while (!done)
        {
          // Fetch the payload, and see if this was the last one.
          done = radio.read( &got_time, sizeof(unsigned long) );
#ifdef USE_SERIAL  
          // Spew it
          printf("Spew Got payload %lu\n",got_time);
#endif//USE_SERIAL
        }
      }

      // Add an ack packet for the next time around.  This is a simple
      // packet counter
      MyStatus stat;
      stat.message_count = message_count;
      stat.potValueA = 42;//potValueA;
      stat.potValueB = 64738;//potValueB;
      stat.unused1 = 2;
      stat.unused2 = sizeof(int);
      radio.writeAckPayload( 1, &stat, sizeof(MyStatus) );
      ++message_count;
    }
  
  
  
//  if (delayA || delayB)
//  {
//    delay(4);
//  }
}

