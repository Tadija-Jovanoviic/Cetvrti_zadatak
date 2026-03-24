/*
Na programskom jeziku C napisati strukturni program kojim se vodi evidencija o drveću u
parku (smatrati da se park pamti kao niz drveća). Podatke o drveću je potrebno modelirati
korišćenjem strukture podataka Drvo, koja je opisana korišćenjem naziva, visine (ceo broj, u
centimetrima), starosti (u godinama) i listopadnosti (smatra se da je drvo listopadno ukoliko je vrednost
postavljena na 1). Napisati funkciju Sortiraj za sortiranje niza drveća u opadajući redosled, po visini.
Napisati funkciju ProsecnaVisinaPoredjenje koja određuje da li je prosečna visina listopadnog drveća
veća od prosečne vrednosti visine zimzelenog drveća (vraća vrednost 1 ukoliko jeste). Smatrati da postoji
makar jedno listopadno i jedno zimzeleno drvo. U glavnom programu dinamički kreirati niz od N drveća,
pri čemu broj elemenata niza i elemente niza (drveće) unosi korisnik sa standardnog ulaza. Na
standardnom izlazu korišćenjem funkcije Sortiraj prikazati najviše drvo (njegov naziv i visinu, vrednosti
odvojene blanko znakom), a potom u nastavku ispisati da li je prosečna visina listopadnog drveća veća od
prosečne visine zimzelenog drveća.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct {
	char naziv[30];
	int visina;
	int starost;
	int listopadno;
} Drvo;
void ZamenaMesta(Drvo* prvoDrvo, Drvo* drugoDrvo)
{
	Drvo pom = *prvoDrvo;
	*prvoDrvo = *drugoDrvo;
	*drugoDrvo = pom;
}
void Sortiraj(Drvo* drvece, int brojDrveca)
{
	for (int i = 0; i < brojDrveca - 1; i++)
	{
		for (int j = i + 1; j < brojDrveca; j++)
		{
			if (drvece[j].visina > drvece[i].visina)
			{
				ZamenaMesta(&drvece[j], &drvece[i]);
			}
		}
	}
}
int ProsecnaVisinaPoredjenje(Drvo drvece[], int brojDrveca)
{
	int ukupna_visina_listopadno = 0, ukupna_visina_cetinari = 0;
	int broj_list = 0, broj_cetinara = 0;
	for (int i = 0; i < brojDrveca; i++)
	{
		if (drvece[i].listopadno == 1)
		{
			ukupna_visina_listopadno += drvece[i].visina;
			broj_list++;
		}
		else
		{
			ukupna_visina_cetinari += drvece[i].visina;
			broj_cetinara++;
		}
	}
	float prosecna_visina_list = (float)ukupna_visina_listopadno / broj_list;
	float prosecna_visina_cetinari = (float)ukupna_visina_cetinari / broj_cetinara;
	return prosecna_visina_list > prosecna_visina_cetinari ? 1 : 0;
}
int main()
	{
		Drvo* drvece;
		int n;
		scanf("%d", &n);
		drvece = (Drvo*)malloc(n * sizeof(Drvo));
		if (drvece != NULL)
		{
			for (int i = 0; i < n; i++)
			{
				scanf("%s%d%d%d", drvece[i].naziv, &drvece[i].visina,
					&drvece[i].starost, &drvece[i].listopadno);
			}
			Sortiraj(drvece, n);
			int prosecna_visina_flag = ProsecnaVisinaPoredjenje(drvece, n);
			printf("%s %d %d", drvece[0].naziv, drvece[0].visina, prosecna_visina_flag);
			free(drvece);
		}
	}