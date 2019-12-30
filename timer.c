#include "colorunner.h" 

//null taster struktura
struct taster taster_null = 
	{.levo = false, .desno = false, .izlaz = false};



void staza_osvezi_stanje()
{
	GLfloat duzina_bloka = (GLfloat)DUZINA_BLOKA;
    
  if(loptica.z >= duzina_bloka)
	{
		//rotacija blokova i repozicioniranje igraca
		loptica.z = loptica.z - duzina_bloka;
		zameni_blok();
  }
}

 

void timer(int timer_val)
{
		
  UNUSED(timer_val);
  struct taster tick;

  tick = trenutni_taster;
	

	//obrade kontrola sa tastature
  if(tick.izlaz)		 
		exit(EXIT_SUCCESS);

   
	if(igra_traje && loptica.anim == NULL)
	{
    if(tick.levo)
		{
			loptica.anim = pokret_strana(-1);
		}
		if(tick.desno)
		{
			loptica.anim = pokret_strana(1);
		}
	}

  if(!igra_pauzirana)
 	{
		if(igra_traje)
		{
			if(++rezultat_timer == TICK_RATE / 4)
			{

				rezultat++;
				rezultat_timer = 0;
			}//povecavamo rezultat 
			rotacija++;
			loptica_osvezi_stanje(); //logika pomeranja igraca i detekcije kolizije
			staza_osvezi_stanje(); //logika ciklicnog pomeranja blokova staze
		}
		else
		{
			//ukoliko je kraj igre iscrtavamo veliku crvenu kuglu na mestu poraza
			iscrtaj_lopticu_kraj();				
		}
  }
 
  trenutni_taster = taster_null;


  glutTimerFunc(TIMER_INTERVAL, timer, TIMER_ID);

  glutPostRedisplay();
}
