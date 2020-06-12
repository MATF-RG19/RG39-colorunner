#include "colorunner.h" 


//promenljive za odredjivanje vremenskog 
//trajanja animacije pomeranja
unsigned int trajanje_pomeraja = 100;
 
	 
//promenljive koje odredjuju velicinu igraca
GLfloat loptica_h = 1;			   
GLfloat polje_w = M_SQRT2;   
GLfloat	polje_h = 1;


 
GLfloat crvenaBoja[] = {.70,.15,  .15, 1};
GLfloat zelenaBoja[] = {.15, .70, .15, 1};
GLfloat plavaBoja[] = {.15, .15,.70, 1};



//promenljive koje opisuju trenutno stanje igre
bool igra_traje;
bool igra_pauzirana;

//rezultat igre
unsigned long long rezultat;
int rezultat_timer;

//za prikaz rotacije loptice
int rotacija;
GLfloat animacija_prolaska;

 
struct taster trenutni_taster;


BLOK *trenutni_blok, *prethodni_blok, *naredni_blok;
LOPTICA loptica;
 
 

//animacija
GLfloat pocetak, kraj;
float t; //od 0 do 1


//animacija pokreta u stranu
bool pomeri_u_stranu(void)
{
  GLfloat razl = kraj - pocetak;

  if(t >= 1.0)
  {
		loptica.x = kraj;	
		return true;
  }
    
		
  loptica.x = pocetak + (GLfloat)sin(t * (M_PI / 2)) * razl;

  t += interval_scale(trajanje_pomeraja);
  return false;
}


anim_t pokret_strana(GLfloat shift)
{
  t = 0.0;
  pocetak = loptica.x;
  kraj = pocetak + shift;

  return pomeri_u_stranu;
}
 
//false ukoliko treba da dodje do kraja igre
bool kolizija_na_polju(int i, int j)
{
	//da li smo ispali van staze
	if(j < 0 || j >= SIRINA_STAZE)
		return false;

 
	//da li je nasa boja ista kao boja prepreke
  if(i >= 0 && i < DUZINA_BLOKA)
  {
		if((*trenutni_blok)[i][j] == CRVENA && izabrana_boja != 0){
    	return false;
		}
		if((*trenutni_blok)[i][j] == ZELENA && izabrana_boja != 1){
    	return false;
		}
 		if((*trenutni_blok)[i][j] == PLAVA && izabrana_boja != 2){
    	return false;
		}
		//randomizacija boje ukoliko smo na polju za promenu
		if((*trenutni_blok)[i][j] == PROMENA){
    	 izabrana_boja = rand() % 3;
				if(izabrana_boja==0){
					memcpy(trenutnaBoja, crvenaBoja, sizeof(GLfloat) * 4);
				}
				else if(izabrana_boja ==1){
					memcpy(trenutnaBoja, zelenaBoja, sizeof(GLfloat) * 4);
				}
				else if(izabrana_boja ==2){
					memcpy(trenutnaBoja, plavaBoja, sizeof(GLfloat) * 4);
				}
	
		}
  }

	//animacija loptice koja raste kada prolazi kroz dobru prepreku
	if((*trenutni_blok)[i][j] == CRVENA || (*trenutni_blok)[i][j] == ZELENA || (*trenutni_blok)[i][j] == PLAVA)
			animacija_prolaska = animacija_prolaska + 0.025;
	//ako nije na prepreci a prethodno je rasla, smanjujemo do nule
	else if(animacija_prolaska > 0)
			animacija_prolaska = animacija_prolaska - 0.025;
	
  return true;
}

//da li je igrac na validnom polju staze
//tj da li je doslo do sudara
bool provera_kolizije()
{
  int i, j;
  
	//trazimo polje na kome se trenutno nalazimo
  i = roundf(loptica.z);
  j = 2 + roundf(loptica.x);

	
  if(kolizija_na_polju(i, j))
		return true;



  return false;
}

//funckija koju poziva timer 
void loptica_osvezi_stanje()
{
  loptica.z += tick_scale(loptica.vz);

	//prekid animacije
  if(loptica.anim != NULL && loptica.anim())
		loptica.anim = NULL;
    
	//provera kolizije sa stazom
  if(igra_traje)
  {
		if(!provera_kolizije())
		{
			//ukoliko je doslo do kolizije prekidamo igru
			igra_traje = false;
		}
  }
}

//inicijalizacija promenljivih za igru
void ucitaj_promenljive()
{
	srand(time(NULL));
	izabrana_boja = rand() % 3;
	if(izabrana_boja==0){
		memcpy(trenutnaBoja, crvenaBoja, sizeof(GLfloat) * 4);
	}
  else if(izabrana_boja ==1){
		memcpy(trenutnaBoja, zelenaBoja, sizeof(GLfloat) * 4);
	}
  else if(izabrana_boja ==2){
		memcpy(trenutnaBoja, plavaBoja, sizeof(GLfloat) * 4);
	}
	


	ucitaj_stazu();

	trenutni_taster = taster_null;

  //pocetna pozicija i brzina igraca
	loptica.x = -1;
	loptica.z = 1;
	loptica.y = 0;


	loptica.vz = 3.0;
	loptica.vx = 0;
	loptica.vy = 0;

	loptica.anim = NULL;
 


	igra_traje = true;
	igra_pauzirana = true;

	rezultat = 0;
	rezultat_timer = 0;
	rotacija = 0;
	animacija_prolaska = 0;
}

