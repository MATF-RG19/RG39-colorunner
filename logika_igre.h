#ifndef _LOGIKAIGRE
#define _LOGIKAIGRE
#include <GL/freeglut.h>
#include <stdbool.h>
#include "timer.h"
#include "staza.h"


#define tick_scale(dist) ((GLfloat)dist / TICK_RATE)

#define interval_scale(msec) (TIMER_INTERVAL / (float)msec)

extern GLfloat loptica_h;
extern GLfloat polje_w;
extern GLfloat polje_h;

typedef bool (*anim_t)(void);
typedef struct
{
	GLfloat x, y, z;
	GLfloat vx, vy, vz;
	anim_t anim;

} LOPTICA;



extern bool igra_traje;
extern bool igra_pauzirana;
extern unsigned long long rezultat;
extern int rotacija;
extern int rezultat_timer;
extern struct taster trenutni_taster;
extern LOPTICA loptica;

 
extern BLOK *trenutni_blok, *prethodni_blok, *naredni_blok;

void loptica_osvezi_stanje();


anim_t pokret_strana(GLfloat);
anim_t pokret_gore();
anim_t pokret_dole();


bool provera_kolizije();
void ucitaj_promenljive();

extern GLfloat zelenaBoja[];
extern GLfloat crvenaBoja[];
extern GLfloat plavaBoja[];

GLfloat trenutnaBoja[4];

int izabrana_boja;


#endif
