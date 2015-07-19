
#include "ofxCrazyradio.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <inttypes.h>

#include "TimeUtils.h"

int main(int argc, char* argv[])
{

  uint64_t startTime = ReadClockTicks();
usleep(500);
 uint64_t deltaTime = ReadClockTicks() - startTime;
printf("usleep(500) test took %" PRIu64" nano seconds (or %2.2gs seconds)\n", TicksToNanoSeconds(deltaTime), TicksToSeconds(deltaTime));

	ofxCrazyradio::Ack* a = 0;
	ofxCrazyradio radio;
	if (!radio.init())
	{
		printf("Error: cannot initialize radio, exiting.\n");
		return -1;
	}

	printf("ok initialized\n");
	 uint8_t address[] = "\xe7\xe7\xe7\xe7\xe7";
	radio.SetAddress(address);
		unsigned char buf[4];//="blaat";//{5,4,3,1,2};
	
	
	printf("SendPacket\n");

	int i=0;
	int success=0;
	int fail=0;

	startTime = ReadClockTicks();
	int numPackets = 100000;	
	for (i=0;i<numPackets;i++)
	{
		
		buf[0]=13;
		buf[1] =127.f-127.f*sin(i/122.);//i>>2;
		buf[2] = 127.f+127.f*sin(i/122.);//i>>2;
		buf[3] = 0;
		
		a = radio.SendPacket((uint8_t*)&buf,4*sizeof(char));	
		if (a && a->ack_received)
		{
			success++;
			
			printf("a->num_retransmission=%d\n", a->num_retransmission);
			printf("a->length=%d\n", a->length);
			for (int i=0;i<a->length;i++)
			{
				int bla = a->data[i];
				printf("data[%d]=%d\n",i,bla);
			}
			 
			 
		} else
		{
			fail++;
		//	printf("no ack received\n");
		}
		//usleep(1000);//any lower and it drops frames
		//sleep(5);
	//	bla=2014;
	//	a = radio.SendPacket((uint8_t*)&bla,sizeof(unsigned long));	
		
	}
	printf("successfull send packets: %d, failed packets:%d\n", success,fail);

	deltaTime = ReadClockTicks() - startTime;
	printf("Roundtrip of %d packets took %" PRIu64" nano seconds (or %2.2gs seconds)\n", numPackets,TicksToNanoSeconds(deltaTime), TicksToSeconds(deltaTime));

#if DEBUG_
	uint8_t channels[1024];	
	int numChannels = radio.ScanChannels(0,1024,channels,1024);
	printf("ScanChannels found %d channels\n",numChannels);	
	for (int i=74;i<77;i++)	
	//for (int i=0;i<numChannels;i++)
	{
		printf("channel[%d]=%d\n",i,channels[i]);
	}
#endif	

	radio.close();
}
