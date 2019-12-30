#ifndef _COLORUNNER
#define _COLORUNNER

#define GL_GLEXT_PROTOTYPES
#define _ISOC99_SOURCE

#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <GL/freeglut.h>
	

#include "staza.h"
#include "logika_igre.h"
#include "timer.h"

#define M_PI  3.141 
#define M_SQRT2 1.414 
#define G_CONST 9.87


//buffer i font za ispis rezultata
#define CHAR_BUFF_SIZE 1024
#define TEKST_FONT  GLUT_BITMAP_HELVETICA_18 

#define UNUSED(arg) ((void)arg)
#define UNUSED_2(arg1, arg2) (UNUSED(arg1), UNUSED(arg2))
 

#endif


