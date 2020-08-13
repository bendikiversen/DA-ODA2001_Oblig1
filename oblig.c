#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

//Global variabel
int a = 0;

struct brukerkonto {
  char brukernavn[100];
  char fornavn   [250]; // alle navn bortsett fra etternavn
  char etternavn [100]; // det siste navnet
};

typedef struct brukerkonto konto_t;

void les_data   (konto_t *brukertabell);
void skriv_data (konto_t *brukertabell);

int main(int argc, char *argv[]) {
  
  //Hent miljøvariablen OBLIG
  char *env = getenv("OBLIG");

  //Sjekk kommandolinje-argument
  if(argc==2){
    if(argv[1][0] == 'b' || argv[1][0] == 'B')
      a = 2;
    else if(argv[1][0] == 'f' || argv[1][0] == 'F')
      a = 1;
  }
  
  //Sjekk miljøvariabel
  else if(env != NULL){
    if(env[0] == 'b' || env[0] == 'B')
      a = 2;
    else if(env[0] == 'f' || env[0] == 'F')
      a = 1;
  }

  konto_t brukertabell[200];
  les_data   (brukertabell);
  skriv_data (brukertabell);

  return 0;
}


void les_data   (konto_t *brukertabell) 
{

  char  *txt = NULL;                      // Peker til lagerplass for innlest linje
  size_t len = 0;                         // Lengde på innlest linje
  int linje = 0;                          // Holder oversikt på hvilken linje som behandles

  while ( -1 != ( len=getline( &txt, &len, stdin ) ) )
  {
    char* kolonne = strtok(txt, ":");     //Tokeniserer data fra standard inngang
    int teller = 0;                       //Teller hvilken token som behandles
    char* brukernavn = NULL;              //Brukernavn
    int uid = 0;                          //UID
    char* fullnavn = NULL;                //Fullt navn

    while(kolonne != NULL)                  //Utfør frem til kolonne peker på NULL
    {
      if(teller == 0)
        brukernavn = kolonne;
      else if(teller == 2)
        uid = atoi(kolonne);                //Fra "string" til "int"
      else if(teller == 4)
      {
        fullnavn = strtok(kolonne,",");     //Ta kun med "full name"
      }
      teller++;
      kolonne = strtok(NULL, ":");          //Til neste token
    }

    if(uid >= 1000)                         //Behandler kun brukere med UID over eller lik 1000
    {
      int lengde = strlen(fullnavn);        //Hent lengden til fullnavn
      char fornavn[lengde];                 //Opprett en char-array med lengden til fullnavn
      strcpy(fornavn,fullnavn);             //Kopier fullnavn til fornavn
      char etternavn[100] = "";             //Opprett en char-array etternavn med lengden 100 og "tomt" innhold
      char* peker = strrchr(fornavn, ' ');  //Bruk strrchr til å gå til siste mellomrom i fornavn (til etternavnet...)
      
      if(peker != NULL)                     //strrchr returnerer NULL dersom den ikke fant noen mellomrom
      {
        int indeks = peker-fornavn+1;       //Indeksen til første tegn etter mellomrom
        int i;
        
        for(i=indeks; i<lengde; i++)
          etternavn[i-indeks] = fornavn[i]; 
        fornavn[indeks-1] = '\0';             //Setter null før etternavnet
      }
      else { strcpy(etternavn,fornavn); }     //Brukeren har ikke flere navn, fornavn = etternavn

      //Kopier brukernavn, fornavn og etternavn til brukertabell
      strcpy(brukertabell[linje].brukernavn, brukernavn);
      strcpy(brukertabell[linje].fornavn, fornavn);
      strcpy(brukertabell[linje].etternavn, etternavn);
      linje++;
    }
  }
  brukertabell[linje+1].brukernavn[0] = '\0';
}

void skriv_data (konto_t *brukertabell) {  
  int i = 0;
  while(brukertabell[i].brukernavn[0] != '\0')
  {   
    switch(a) {
      case 0:
        printf("%s,%s,%s\n", brukertabell[i].etternavn, brukertabell[i].fornavn, brukertabell[i].brukernavn);
        break;
      case 1:
        printf("%s,%s,%s\n", brukertabell[i].fornavn, brukertabell[i].etternavn, brukertabell[i].brukernavn);
        break;
      case 2:
        printf("%s,%s,%s\n", brukertabell[i].brukernavn, brukertabell[i].etternavn, brukertabell[i].fornavn);
        break;
    }
     i++;
  }
}
