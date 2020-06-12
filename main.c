#include "colorunner.h" 

 
void keyboard(unsigned char, int, int);
void special(int, int, int);
void start_game();
void reshape(int, int);
void display(void);
static void inicijalizacijaTekstura(void);
 

#define FILENAME0 "textures/pocetna_slika.bmp"
#define FILENAME1 "textures/podloga.bmp"

GLuint textures[2];





void keyboard(unsigned char key, int x, int y)
{
  UNUSED_2(x, y);

  switch(key)
  {
	  case 'q':
		case 'Q':
			trenutni_taster.izlaz = true;
			break;
		case 'p':
		case 'P':
			igra_pauzirana = !igra_pauzirana;	
      glutDisplayFunc(display);	 
			break;
    default:
			break;
  }
}

void special(int key, int x, int y)
{
	UNUSED_2(x, y);
  switch(key)
  {
		case GLUT_KEY_LEFT:
			trenutni_taster.levo = true;
			break;
    case GLUT_KEY_RIGHT:
			trenutni_taster.desno = true;
			break;
    default:
			break;
  }
}
//za promenu velicine prozora
void reshape(int width, int height)
{
  GLdouble near = -16, far = 16;
  GLdouble clip = M_PI * 2;
  GLdouble ah, aw;
	glViewport(0, 0, width, height);
 
  aw = (float)height / width;
  ah = 1.0;
 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-clip * ah, clip * ah,
    			-clip * aw, clip * aw,
	   			 near, far);
 
  glutPostRedisplay();
}

void display(void)
{
  glClearColor(0, 0.5, 0.99, 0);
  glEnable(GL_DEPTH_TEST);

  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);  //inicijalizacija buffera
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//iscrtavanje scene
  glMatrixMode(GL_MODELVIEW);
	postavi_scenu();
	iscrtaj_scenu();
	iscrtavanje_rezultata();



  glutSwapBuffers();
}
static void inicijalizacijaTekstura(void){
    /*funkcija sa sedmog casa vezbi koja koristi biblioteku image.c*/

    Image * image;
    glEnable(GL_DEPTH_TEST);

    /*ukljucivanje odredjenih flegova za lepljenje tekstura*/
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

    /*inicijalizacija*/
    image = image_init(0, 0);

    glGenTextures(2, textures);

 
  image_read(image, FILENAME0);

    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	 



  image_read(image, FILENAME1);

    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	 

    /*Iskljucujemo aktivnu teksturu*/
    glBindTexture(GL_TEXTURE_2D, 0);

    image_done(image);
}

int main(int argc, char* argv[])
{
  glutInitWindowSize(1024, 768);
  glutInit(&argc, argv);
  glutSetOption(GLUT_MULTISAMPLE, 8);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE);

  glutCreateWindow("Colorunner - RG");
	inicijalizacijaTekstura();


 


  glutDisplayFunc(display);
  glutDisplayFunc(start_game);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutTimerFunc(TIMER_INTERVAL, timer, TIMER_ID);
  glutReshapeFunc(reshape);





 


  ucitaj_promenljive();
	
  glutMainLoop();
  return EXIT_FAILURE;
}

void start_game(void)
{  glClearColor(0, 0.5, 0.99, 0);
 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 2, 0,
              0, 0, 0,
              1, 0, 0);

    GLfloat light_position[] = {0, 0, 0, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glBegin(GL_POLYGON);
        glNormal3f(0, 1, 0);

        glTexCoord2f(0, 0);
        glVertex3f(-1, 0, -1.5);

        glTexCoord2f(0, 1);
        glVertex3f(1, 0, -1.5);

        glTexCoord2f(1, 1);
        glVertex3f(1, 0, 1.5);

        glTexCoord2f(1, 0);
        glVertex3f(-1 ,0, 1.5);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glutSwapBuffers();
}


