#include "colorunner.h" 
extern GLuint textures[2];
int blok_trenutni;
BLOK baza_blokova[3];

void postavi_plocu(BLOK blk, int i, int j)
{
	blk[i][j] = PLOCA;
}
void postavi_crvenu(BLOK blk, int i, int j)
{ 
	blk[i][j] = CRVENA;
}
void postavi_plavu(BLOK blk, int i, int j)
{ 
	blk[i][j] = PLAVA;
}
void postavi_zelenu(BLOK blk, int i, int j)
{ 
	blk[i][j] = ZELENA;
}
void postavi_promenu_boje(BLOK blk, int i, int j)
{ 
	blk[i][j] = PROMENA;
}

void postavi_rupe(BLOK blk)
{
  memset(blk, RUPA, sizeof(BLOK));
}

void inicijalizuj_blok(BLOK blk)
{
  int i, j;
	int prepreka = 0;
	int promena_boje = 0;

	//prolazimo kroz ceo blok
  for(i = 0; i < DUZINA_BLOKA; i++)
	{
		int p, order;
		//ukoliko je igra tek pocela
		//inicijalizujemo prvi blok kao ploce
		//da bismo sprecili 'spawn kill' :)
		if(rezultat == 0 || i == 0 || promena_boje != 0 || prepreka != 0)
		{
			if(prepreka>0)
				prepreka--;
			if(promena_boje>0)
				promena_boje--;
			for(j = 0; j < SIRINA_STAZE ; j++)
			{
				postavi_plocu(blk, i, j);
			}
			continue;
		}
 


 		p = rand()%10;
		//40% sanse da postavljamo prepreku
		if(p<=4){
			//redosled postavljanja obojenih prepreka, postoji 6 kombinacija
			order = rand()%6;
			prepreka = 2;
		}
		//10% sanse da postavljamo promenu boje
		if(p == 5){
			promena_boje =2 ;
		}
		for(j = 0; j<SIRINA_STAZE; j++)
		{
			if(prepreka > 0){
				if(order == 0){
					postavi_crvenu(blk, i, j);
					postavi_plavu(blk, i, j+1);
					postavi_zelenu(blk, i, j+2);
				}
				else if(order == 1){
					postavi_crvenu(blk, i, j);
					postavi_zelenu(blk, i, j+1); 
					postavi_plavu(blk, i, j+2);
				}
				else if(order == 2){
					postavi_plavu(blk, i,j);
					postavi_crvenu(blk, i, j+1); 
					postavi_zelenu(blk, i, j+2);
				}
				else if(order == 3){
					postavi_plavu(blk, i, j);
					postavi_zelenu(blk, i,j+1); 
					postavi_crvenu(blk, i, j+2);
				}
				else if(order == 4){
					postavi_zelenu(blk, i, j);
					postavi_crvenu(blk, i,j+1); 
					postavi_plavu(blk, i, j+2);
				}
				else if(order == 5){
					postavi_zelenu(blk, i, j);
					postavi_plavu(blk, i, j+1); 
					postavi_crvenu(blk, i,  j+2);
				}
				break;
			}
			else if(promena_boje >0 ){
					postavi_promenu_boje(blk, i, j);
					postavi_promenu_boje(blk, i, j);
					postavi_promenu_boje(blk, i, j);
			}
			else{
				postavi_plocu(blk, i, j);
			}

		}
	}
}
//postavljanje pokazivaca na blokove
void postavi_pokazivace_blokovi()
{
  prethodni_blok = &baza_blokova[(blok_trenutni) % 3];
  trenutni_blok = &baza_blokova[(blok_trenutni + 1) % 3];
  naredni_blok = &baza_blokova[(blok_trenutni + 2) % 3];
}

void ucitaj_stazu()
{
 
   
  postavi_rupe(baza_blokova[0]); //na pocetku iza nas prazno
  inicijalizuj_blok(baza_blokova[1]); //inicijalizujemo trenutni
  inicijalizuj_blok(baza_blokova[2]); //i naredni
	
  blok_trenutni = 0;
  postavi_pokazivace_blokovi();
}

void zameni_blok()
{
  //menjamo trenutni blok
  blok_trenutni = (blok_trenutni + 1) % 3;
  postavi_pokazivace_blokovi();

	//inicijalizujemo naredni
  inicijalizuj_blok(*naredni_blok);
}

//iscrtavanje polja u zavisnosti od njegovog tipa
void iscrtaj_polje(enum polje _polje)
{
	//boje
  GLfloat bojaPolja[] =  {.7, .7, .7, 1};
	 
  GLfloat bojaPromene[] =  {0.9, .1, .4, 1};

  GLfloat *osnova = NULL;


  if(_polje == PLOCA)
	{
		osnova = bojaPolja;
	 	glMaterialfv(GL_FRONT , GL_AMBIENT_AND_DIFFUSE, osnova);
		glShadeModel(GL_SMOOTH);

		glPushMatrix();
		glScalef(polje_w, polje_h, polje_w);
		glutSolidCube(1);
		glPopMatrix();

	}
	else if(_polje == CRVENA)
	{
		osnova = crvenaBoja;
	 	glMaterialfv(GL_FRONT , GL_AMBIENT_AND_DIFFUSE, osnova);
		glShadeModel(GL_SMOOTH);

		glPushMatrix();
		glTranslatef(0,0.25,0);
		glScalef(polje_w, polje_h*1.5, polje_w);
		glutSolidCube(1);
		glPopMatrix();
	}
	else if(_polje == ZELENA)
	{
		osnova = zelenaBoja;
	 	glMaterialfv(GL_FRONT , GL_AMBIENT_AND_DIFFUSE, osnova);
		glShadeModel(GL_SMOOTH);

		glPushMatrix();
		glTranslatef(0,0.25,0);
		glScalef(polje_w, polje_h*1.5, polje_w);
		glutSolidCube(1);
		glPopMatrix();
	}
	else if(_polje == PLAVA)
	{
		osnova = plavaBoja;
	 	glMaterialfv(GL_FRONT , GL_AMBIENT_AND_DIFFUSE, osnova);
		glShadeModel(GL_SMOOTH);

		glPushMatrix();
		glTranslatef(0,0.25,0);
		glScalef(polje_w, polje_h*1.5, polje_w);
		glutSolidCube(1);
	 
		glPopMatrix();
	}
	else if(_polje == PROMENA)
	{
			glPushMatrix();
			glScalef(polje_w, polje_h, polje_w);
	 
		glTranslatef(0,-0.5,0);
				GLfloat vertices[] =
		 {-0.5f, 0.0f, 0.5f,   0.5f, 0.0f, 0.5f,   0.5f, 1.0f, 0.5f,  -0.5f, 1.0f, 0.5f,
			-0.5f, 1.0f, -0.5f,  0.5f, 1.0f, -0.5f,  0.5f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f,
			0.5f, 0.0f, 0.5f,   0.5f, 0.0f, -0.5f,  0.5f, 1.0f, -0.5f,  0.5f, 1.0f, 0.5f,
			-0.5f, 0.0f, -0.5f,  -0.5f, 0.0f, 0.5f,  -0.5f, 1.0f, 0.5f, -0.5f, 1.0f, -0.5f
			};

		 GLfloat texcoords[] = { 0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
				                           0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
				                           0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
				                           0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0
				                         };

		 GLubyte cubeIndices[24] = {0,1,2,3, 4,5,6,7, 3,2,5,4, 7,6,1,0,
				                              8,9,10,11, 12,13,14,15};


	 glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glColor3f(1.0f, 1.0f, 1.0f);

        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);

        glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
        glVertexPointer(3, GL_FLOAT, 0, vertices);

        glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
        glDisableClientState(GL_VERTEX_ARRAY);
        //glDisableClientState(GL_COLOR_ARRAY);
        glDisable(GL_TEXTURE_2D);

		glPopMatrix();
	}
 
}

//iscrtavanje sfere
void iscrtaj_lopticu()
{
 
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, trenutnaBoja);
  glShadeModel(GL_SMOOTH);

  glPushMatrix();
  glTranslatef(loptica.x * polje_w, loptica.y * polje_w, 0);
	//animacija kotrljanja
	glRotatef(-2.25*rotacija, 1, 0, 0);
  glutSolidSphere(0.3+animacija_prolaska, 10, 10);
 
  glPopMatrix();
}

//crna sfera kao znak kolizije i kraja igre
void iscrtaj_lopticu_kraj()
{
  GLfloat material_base[] = {.2, .2, .2, 0.8};
  
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material_base);
  glShadeModel(GL_SMOOTH);

  glPushMatrix();
  glTranslatef(loptica.x * polje_w, loptica.y * polje_w, 0);
  glutSolidSphere(0.5, 10, 10);
  glPopMatrix();
}

//iscrtavanje bloka polja
void iscrtaj_blok(BLOK *blok_p, int offset)
{
  GLfloat blok_z_off = -(polje_w * (DUZINA_BLOKA * offset));
  int i, j;

  glPushMatrix();
  glTranslatef(0, 0, blok_z_off);

  for(i = 0; i < DUZINA_BLOKA; i++)
	{
		for(j = 0; j < SIRINA_STAZE; j++)
		{
			enum polje trenutno_polje = (*blok_p)[i][j];
				
 
			glPushMatrix();
			glTranslatef(polje_w * j, 0, -polje_w * i);
			iscrtaj_polje(trenutno_polje);
			glPopMatrix();
		}
  }
  glPopMatrix();
}

void iscrtaj_stazu()
{
	//igrac stoji na stazi ravno
  GLfloat staza_y_offset = -(loptica_h + polje_h) / 2;
  GLfloat staza_x_offset = -(2 * polje_w);

  glPushMatrix();
  glTranslatef(staza_x_offset,
							staza_y_offset,
							loptica.z * polje_w);

	//crtanje blokova staze
  iscrtaj_blok(prethodni_blok, OFFSET_PREV);
  iscrtaj_blok(trenutni_blok, OFFSET_CURR);
  iscrtaj_blok(naredni_blok, OFFSET_NEXT);
  
  glPopMatrix();
}

void postavi_scenu()
{
  GLdouble dist = 3.0;
  GLdouble z = -(2 * M_SQRT2);
  GLdouble dist_z = dist + z;

 	GLfloat directional_position[] = {3,2, -1, 0.2};
  GLfloat directional_diffuse[] = {.88 , .88, .88, 1};
  GLfloat ambient_light[] = {.55, .55, .55, 1};

	
	//pogled i kamera
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
	glTranslatef(4,0,0); //centriramo sliku
  gluLookAt(dist, dist, dist_z,	 
				      2.5, 0.8, z,		         
				      0, 1, 0); //pozicioniranje kamere		        

	//staticko svetlo
  glLightfv(GL_LIGHT0, GL_POSITION, directional_position);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, directional_diffuse);

  //ambijentalno svetlo
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_light);
  
  glEnable(GL_LIGHT0);
}

void iscrtaj_scenu()
{
  iscrtaj_stazu();
	if(igra_traje)
  	iscrtaj_lopticu();
	else
  	iscrtaj_lopticu_kraj();
}

void iscrtavanje_rezultata()
{
  char rezultat_buff[CHAR_BUFF_SIZE];
 
  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);

  if(igra_traje && !igra_pauzirana)
		snprintf(rezultat_buff, CHAR_BUFF_SIZE, "%lld", rezultat);
  else if (igra_traje && igra_pauzirana)
		snprintf(rezultat_buff, CHAR_BUFF_SIZE, "GAME PAUSED");
	else
		snprintf(rezultat_buff, CHAR_BUFF_SIZE, "FINAL SCORE: %lld", rezultat);
    
	//boja rezultata
	if(izabrana_boja == 0)
  	glColor4f(.70,.15,  .15, 1);
	else if(izabrana_boja == 1)
  	glColor4f(.15,  .70, .15, 1);
	else if(izabrana_boja == 2)
  	glColor4f(.15,  .15,.70,1);



  glWindowPos2i(25,  glutGet(GLUT_WINDOW_HEIGHT) - 2 - glutBitmapHeight(TEKST_FONT));
  glutBitmapString(TEKST_FONT, (const unsigned char *)rezultat_buff);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
}
