#ifndef _STAZA
#define _STAZA

#define SIRINA_STAZE 3
#define DUZINA_BLOKA 10
 
//tipovi polja
enum polje
{
  PLOCA, CRVENA,ZELENA, PLAVA, RUPA, PROMENA
};

enum
{
  OFFSET_PREV = -1,
  OFFSET_CURR,
  OFFSET_NEXT
};

typedef enum polje BLOK[DUZINA_BLOKA][SIRINA_STAZE];

void init_track();
void cycle_track();

void ucitaj_stazu();
void iscrtaj_lopticu_kraj();
void iscrtaj_scenu();
void postavi_scenu();
void iscrtavanje_rezultata();

#endif
