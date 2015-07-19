#ifdef __APPLE__
#include "/usr/local/include/libusb-1.0/libusb.h"
#endif

#include "ofxCrazyradio.h"
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#ifdef __APPLE__
#include <mach/mach_time.h>
uint64_t ReadTicks( void )
{
    return mach_absolute_time();
}
double  TicksToSeconds( uint64_t delta )
{
    static long double conversion = 0.0L;
    if( 0.0L == conversion )
    {
        // attempt to get conversion to nanoseconds
        mach_timebase_info_data_t info;
        int err = mach_timebase_info( &info );
        if( err )
            return __builtin_nanf("");
        conversion = info.numer / (1e9L * info.denom);
    }

    return (double) (delta * conversion);
}
#else
#include <sys/time.h>

uint64_t ReadTicks( void )
{
	timespec ts;
	clock_gettime(CLOCK_REALTIME,&ts);

	return 1000000000*ts.tv_sec + ts.tv_nsec;
}
double  TicksToSeconds( uint64_t delta )
{
return delta/1e9;
}
#endif

int main(int argc, char* argv[])
{
	ofxCrazyradio::Ack* a = 0;
	ofxCrazyradio radio;
	if (radio.init())
	{
	printf("ok initialized\n");
	 uint8_t address[] = "\xe7\xe7\xe7\xe7\xe7";
	radio.SetAddress(address);
		unsigned char buf[4];//="blaat";//{5,4,3,1,2};
	//unsigned long bla=12345;
	
	
	printf("SendPacket\n");
//	a = radio.SendPacket((uint8_t*)buf,4);
	//	a = radio.SendPacket((uint8_t*)&bla,sizeof(unsigned long));	
		printf("SendPackets\n");

		int i=0;
		int success=0;
		int fail=0;

 uint64_t startTime = ReadTicks();

		
	for (i=0;i<1000000;i++)
	{
		
		buf[0]=13;
		buf[1] =127.f-127.f*sin(i/122.);//i>>2;
		buf[2] = 127.f+127.f*sin(i/122.);//i>>2;
		buf[3] = 0;
		//printf("bla = %d\n", bla);
		
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

   uint64_t currentTime = ReadTicks() - startTime;
         printf("It took (%2.2gs) seconds\n", TicksToSeconds(currentTime));


	
#if 0
	uint8_t channels[1024];	
	int numChannels = radio.ScanChannels(0,1024,channels,1024);
	printf("ScanChannels found %d channels\n",numChannels);	
	for (int i=74;i<77;i++)	
	//for (int i=0;i<numChannels;i++)
	{
		printf("channel[%d]=%d\n",i,channels[i]);
	}
#endif	
} else
{
	printf("cannot initialize\n");
}
	radio.close();
}
