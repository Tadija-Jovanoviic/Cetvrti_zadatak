/*
 Na programskom jeziku C napisati strukturni program kojim se vodi evidencija o ribicama u
akvarijumu. Podatke o ribicama je potrebno modelirati korišćenjem strukture podataka Ribica koja je
opisana korišćenjem naziva vrste, težine (ceo broj, u gramima) i njenoj boji. Napisati funkciju Sortiraj za
sortiranje niza ribica u opadajući redosled, po težini. Napisati funkciju IzbaciPredatore koja izbacuje iz
akvarijuma sve ribice koje mogu da pojedu neku drugu ribicu. Smatrati da će ribica pojesti drugu ribicu
ukoliko ima 10 puta veću težinu.
Na standardnom izlazu, korišćenjem funkcije Sortiraj prikazati najtežu ribicu (njen naziv, boju i težinu,
vrednosti odvojene blanko znakom), a potom ukloniti sve predatore i prikazati podatke o ribicama koje
ostaju u akvarijumu (njihov naziv, boju i težinu, vrednosti odvojene blanko znakom). Odvojiti štampu
najteže ribice od ribica koje ostaju u akvarijumu novim redom.
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
	char naziv[30];
	int tezina;
	char boja;
} Ribica;
void ZamenaMesta(Ribica* r1, Ribica* r2)
{
Ribica pom = *r1;
*r1 = *r2;
*r2 = pom;
}
void Sortiraj(Ribica* ribice, int brojRibica)
{
	for (int i = 0; i < brojRibica - 1; i++)
	{
		for (int j = i + 1; j < brojRibica; j++)
		{
			if (ribice[j].tezina > ribice[i].tezina)
			{
				ZamenaMesta(&ribice[j], &ribice[i]);
			}
		}
	}
}
int IzbaciPredatore(Ribica ribice[], int brojRibica)
{
	int i = 0, j;
	while (i < brojRibica - 1)
	{
		j = i + 1;
		while (j < brojRibica && (ribice[j].tezina * 10) >= ribice[i].tezina)
		{
			j++;
		}
		if (j < brojRibica)
		{
			// uklanjanje ribice
			for (j = i; j < brojRibica - 1; j++)
			{
				ribice[j] = ribice[j + 1];
			}
			brojRibica--;
		}
		else
			i++;
	}
	return brojRibica;
}
int main()
{
	Ribica* ribice;
	int n, i, noviBrojRibica;
	scanf("%d", &n);
	ribice = (Ribica*)malloc(n * sizeof(Ribica));
	if (ribice != NULL)
	{
		for (i = 0; i < n; i++)
			scanf("%s %d %s\n", ribice[i].naziv, &ribice[i].tezina, ribice[i].boja);

		Sortiraj(ribice, n);
		printf("%s %d %s\n", ribice[0].naziv, ribice[0].tezina, ribice[0].boja);
		printf("\n");

		noviBrojRibica = IzbaciPredatore(ribice, n);
		for (i = 0; i < noviBrojRibica; i++)
			printf("%s %d %s\n", ribice[i].naziv, ribice[i].tezina, ribice[i].boja);
		free(ribice);
	}
}