#ifndef _TIMER
#define _TIMER

#include <stdbool.h>

#define TIMER_ID 15		 
#define SEC_INTERVAL 1000
#define TICK_RATE 50            
 
#define TIMER_INTERVAL (SEC_INTERVAL / TICK_RATE)


void timer(int);
void zameni_blok();
//naredbe koje se salju preko tastature
struct taster
{
  bool levo;
  bool desno;
  bool gore;
	bool dole;
  bool izlaz;
};

extern struct taster taster_null;

#endif
