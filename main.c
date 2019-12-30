#include "colorunner.h" 

 
void keyboard(unsigned char, int, int);
void special(int, int, int);
void reshape(int, int);
void display(void);

 
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
  //inicijalizacija buffera
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//iscrtavanje scene
  glMatrixMode(GL_MODELVIEW);
	iscrtaj_scenu();
	iscrtavanje_rezultata();
      
  glutSwapBuffers();
}

int main(int argc, char* argv[])
{
  glutInitWindowSize(1024, 768);
  glutInit(&argc, argv);
  glutSetOption(GLUT_MULTISAMPLE, 8);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE);

  glutCreateWindow("Colorunner - RG");


  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutTimerFunc(TIMER_INTERVAL, timer, TIMER_ID);
  glutReshapeFunc(reshape);


  glClearColor(0, 0.5, 0.99, 0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);


  postavi_scenu();


  ucitaj_promenljive();
	
  glutMainLoop();
  return EXIT_FAILURE;
}
