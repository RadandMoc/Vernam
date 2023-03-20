#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

 unsigned char* losowyklucz(int dlugoscKlucza)
{
    unsigned char* klucz = (char*) malloc(sizeof(*klucz) * dlugoscKlucza);
    srand(time( NULL));
    for(int i=0;i<dlugoscKlucza; i++)
        {
        klucz[i]=rand()%94+33;
        }
    return klucz;
}

unsigned char* szyfrowanie(unsigned char *wyraz,int dlugoscWyrazu,unsigned char *c, int dlugoscKlucza)
{
    int i=0;

        while (i<=dlugoscWyrazu)
        {
            if(wyraz[i]>=33 && wyraz[i]<=126)
            {
                if(wyraz[i]+(c[i%dlugoscKlucza]-33)<127)
                {
                    wyraz[i]=wyraz[i]+c[i%dlugoscKlucza]-33;
                }
                else
                {
                    wyraz[i]=33+((wyraz[i]+(c[i%dlugoscKlucza]-33))%127);
                }
            }
        ++i;
        }
    return wyraz;
}


unsigned char* deszyfracja(unsigned char *wyraz,int dlugoscWyrazu,unsigned char *c, int dlugoscKlucza)
{
    int i=0;

 while (i<=dlugoscWyrazu)
        {
            if (wyraz[i]>=33 && wyraz[i]<=126)
            {
                if(wyraz[i]-(c[i%dlugoscKlucza])>=0)
                {
                    wyraz[i]=wyraz[i]-(c[i%dlugoscKlucza]-33);
                }
                else
                {
                    wyraz[i]=127+wyraz[i]-c[i%dlugoscKlucza];
                }
            }
        ++i;
        }
    return wyraz;
}


int czytaj_plik_zwroc_dlugosc(unsigned char *tablica, char* nazwapliku)
{
    int a=0,b=1;
    unsigned char* bufor=(unsigned char*) malloc(sizeof(*bufor) * 200);
    FILE * plik;
    plik = fopen(nazwapliku, "r");
    int liczba=0;
    while(a<b)
    {
        fgets(bufor, 200, plik);
        int pomocnicza=0;
        while(bufor[pomocnicza]!='\0')
        {
            tablica[liczba]=bufor[pomocnicza];
            ++liczba;
            ++pomocnicza;
            if(tablica[liczba-1]=='\n')
                {
                b=b+1;
                }
        }

        a++;
    }
    fclose(plik);
    tablica[liczba]='\0';
    return liczba;
}


unsigned char* klucz()
{
    unsigned char* wynik = (char*) malloc(sizeof(*wynik) * 1000);
    printf("Podaj klucz do zakodowania wiadomosci \n");
    int i=0;
    scanf("%s",wynik);
    int kot = strlen(wynik);
    //printf("%d",kot);
    wynik = realloc(wynik,(sizeof(*wynik)*(1000-kot)));
    printf("%s",wynik);
    return wynik;
}


unsigned char* tresc()
{
unsigned char* wynik = (char*) malloc(sizeof(*wynik) * 1000);
printf("Podaj tresc do zakodowania/odszyfrowania wiadomosci \n");
int i=0;
scanf("%s",wynik);
return wynik;
}


void dopliku(unsigned char* wynik,int liczba)
{
    time_t t;
    struct tm* timeinfo;
    time(&t);
    timeinfo = localtime(&t);
    char nazwapliku[24];
    int data[6];
    data[0]= timeinfo->tm_hour;
    data[1]= timeinfo->tm_min;
    data[2]= timeinfo->tm_sec;
    data[3]= (timeinfo->tm_year)+1900;
    data[4]= (timeinfo->tm_mon)+1;
    data[5]= timeinfo->tm_mday;
    if (liczba==0)
        {
        sprintf(nazwapliku,"k_%d%d%d%d%d%d.txt",data[3],data[4],data[5],data[0],data[1],data[2]);
        FILE * plik;
        plik  = fopen(nazwapliku, "w");
        fprintf (plik, "%s", wynik);
        fclose (plik);
        }
    else if (liczba==1)
        {
        sprintf(nazwapliku,"dc_%d%d%d%d%d%d.txt",data[3],data[4],data[5],data[0],data[1],data[2]);
        FILE * plik;
        plik  = fopen(nazwapliku, "w");
        fprintf (plik, "%s", wynik);
        fclose (plik);
        }
    else
        {
        sprintf(nazwapliku,"cd_%d%d%d%d%d%d.txt",data[3],data[4],data[5],data[0],data[1],data[2]);
        FILE * plik;
        plik  = fopen(nazwapliku, "w");
        fprintf (plik, "%s", wynik);
        fclose (plik);
        }
}


int main()
{
  int menu;
  short int czy=0;
  do{
      printf("Jezeli chcesz zaszyfrowac tresc nacisnij 1\nJezeli chcesz zaszyfrowac plik (losowyklucz) to nacisnij 2\nJezeli chcesz zaszyfrowac plik (klucz z pliku) to nacisnij 3\nJezeli chcesz odszyfrowac tresc to nacisnij 4\nJezeli chcesz odszyfrowac plik to nacisnij 5\nJezeli chcesz wylaczyc program nacisnij 6\n");
      scanf("%d",&menu);

    if (menu==1)
      {
        unsigned char *wsk4 =klucz();
        unsigned char *wsk5 = tresc();
        int d=strlen(wsk5);
        int k=strlen(wsk4);
        printf("Czy chcesz zapisac klucz do pliku? 1 - Tak 0 - Nie \n");
        scanf("%d",&czy);
        printf("%s",wsk4);
        if(czy==1)
            {
            dopliku(wsk4,0);
            }

        printf("Czy chcesz zapisac zaszyfrowana wiadomosc do pliku? 1 - Tak 0 - Nie \n");
        scanf("%d",&czy);
        unsigned char *wsk3 = szyfrowanie(wsk5,d,wsk4,k);
        if(czy==1)
            {
            dopliku(wsk3,2);
            }
        printf("Zaszyfrowana wiadomosc:\n%s\n",wsk3);

        unsigned char *wsk6 = deszyfracja(wsk3,d,wsk4,k);
        printf("Czy chcesz zapisac wiadomosc do pliku? 1 - Tak 0 - Nie \n");
        scanf("%d",&czy);
        if (czy==1)
        {
            dopliku(wsk6,1);

        }
        free(wsk4);
        free(wsk5);
        menu=1;
        }
    else if (menu==2)
        {
        int liczba;
        char nazwa[20];
        printf("Podaj nazwe pliku\n");
        scanf("%s",nazwa);
        unsigned char *tablica = (unsigned char*) malloc(sizeof(*tablica) * 1000);
        liczba = czytaj_plik_zwroc_dlugosc(tablica,nazwa);
        printf("Czy chcesz zapisac klucz do pliku? 1 - Tak 0 - Nie \n");
        unsigned char *wsk= losowyklucz(liczba);
        scanf("%d",&czy);
        if (czy==1)
            {
            dopliku(wsk,0);
            }
        printf("Losowy Klucz: %s",wsk);

        printf("\nCzy chcesz zapisac zaszyfrowana wiadomosc do pliku? 1 - Tak 0 - Nie \n");
        scanf("%d",&czy);
        unsigned char *wsk2 = szyfrowanie(tablica,liczba,wsk,liczba);
        if (czy==1)
            {
            dopliku(wsk2,2);
            }
        menu=2;

        }
    else if (menu==3)
        {
        int liczba;
        char nazwa[20];
        printf("Podaj nazwe pliku \n");
        scanf("%s",nazwa);
        unsigned char *tablica[1000];
        liczba = czytaj_plik_zwroc_dlugosc(tablica,nazwa);
        char nazwaplikuklucz[20];
        printf("Podaj nazwe pliku z kluczem \n");
        scanf("%s",nazwaplikuklucz);
        unsigned char *klucz[1000];

        int dlugoscKlucza = czytaj_plik_zwroc_dlugosc(klucz, nazwaplikuklucz);
        unsigned char *wsk2 = szyfrowanie(tablica,liczba,klucz,dlugoscKlucza);
        printf("Czy chcesz zapisac zaszyfrowana wiadomosc do pliku? 1 - Tak 0 - Nie \n");
        scanf("%d",&czy);
        if (czy==1)
        {
           dopliku(wsk2,2);
        }
        printf("Zaszyfrowana Wiadomosc\n%s\n",wsk2);
        menu=3;

        }
    else if (menu==4)
        {
        unsigned char *wsk =klucz();
        unsigned char *wsk2 = tresc();
        int d=strlen(wsk2);
        int dlugoscKlucza=strlen(wsk);
        unsigned char *wsk3 = deszyfracja(wsk2,d,wsk,dlugoscKlucza);
        printf("Czy chcesz zapisac zdeszyfrowana wiadomosc do pliku? 1 - Tak 0 - Nie \n");
        scanf("%d",&czy);
        if (czy==1)
        {
           dopliku(wsk3,1);
        }
        printf("%s\n",wsk3);
        menu=4;
        }
      else if (menu==5)
        {
        int liczba;
        char nazwa[20];
        printf("Podaj nazwe pliku z zakodowana wiadomoscia \n");
        scanf("%s",&nazwa);
        unsigned char *tablica[1000];
        liczba = czytaj_plik_zwroc_dlugosc(tablica,nazwa);

        char nazwaplikuklucz[20];
        printf("Podaj nazwe pliku z kluczem ");
        scanf("%s",&nazwaplikuklucz);

        unsigned char *klucz[1000];
        int dlugoscKlucza = czytaj_plik_zwroc_dlugosc(klucz, nazwaplikuklucz);

        unsigned char *wsk2 = deszyfracja(tablica,liczba,klucz,dlugoscKlucza);
        printf("Czy chcesz zapisac zdeszyfrowana wiadomosc do pliku? 1 - Tak 0 - Nie \n");
        scanf("%d",&czy);
        if (czy==1)
            {
            dopliku(wsk2,1);
            }
        printf("Zdeszyfrowana wiadomosc %s\n",wsk2);
        menu=5;
        }

        }while(menu>0&&menu<6);
  return 0;
}
