/*
Na programskom jeziku C napisati strukturni program kojim se vodi evidencija o proizvodima u
prodavnici. Podatke o proizvodima je potrebno modelirati koriscenjem strukture podataka Proizvod,
koja je opisana koriscenjem: naziva, cene (realan broj), kolicine na stanju (ceo broj) i
kategorije (prehrambeni = 1, neprehrambeni = 0). Napisati funkciju SortirajPoCeni za sortiranje
niza proizvoda u rastuci redosled po ceni. Napisati funkciju UkupnaVrednostRazlika koja racuna
razliku izmedju ukupne vrednosti (cena * kolicina) prehrambenih proizvoda i ukupne vrednosti
neprehrambenih proizvoda (smatrati da postoji makar jedan proizvod svake kategorije). U glavnom
programu dinamicki kreirati niz od N proizvoda, pri cemu broj proizvoda i same proizvode unosi
korisnik sa standardnog ulaza. Na standardnom izlazu prikazati naziv i cenu najjeftinijeg
proizvoda (koriscenjem funkcije SortirajPoCeni), a potom u nastavku ispisati razliku ukupnih
vrednosti.*/
#include<stdio.h>
#include<stdlib.h>
typedef struct {
	char naziv[20];
	float cena;
	int kolicina_na_stanju;
	int kategorija; // prehrambeni = 1, neprehrambeni = 0;
} Proizvod;
void ZamenaMesta(Proizvod* prvi_proizvod, Proizvod* drugi_proizvod)
{
	Proizvod pom = *prvi_proizvod;
	*prvi_proizvod = *drugi_proizvod;
	*drugi_proizvod = pom;
}
void SortirajPoCeni(Proizvod* proizvodi, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (proizvodi[i].cena > proizvodi[j].cena)
			{
				ZamenaMesta(&proizvodi[i], &proizvodi[j]);
			}
		}
	}
}
float UkupnaVrednostRazlika(Proizvod* proizvodi, int n)
{ 
float ukupna_cena_prehrambeni = 0, ukupna_cena_neprehrambeni = 0;
for (int i = 0; i < n; i++)
{
	if (proizvodi[i].kategorija == 1)
	{
		ukupna_cena_prehrambeni += proizvodi[i].cena * proizvodi[i].kolicina_na_stanju;
	}
	else
	{
		ukupna_cena_neprehrambeni += proizvodi[i].cena * proizvodi[i].kolicina_na_stanju;
	}
}
	return ukupna_cena_prehrambeni - ukupna_cena_neprehrambeni;
}
int main()
{
	Proizvod* proizvodi;
	int n;
	scanf("%d", &n);
	proizvodi = (Proizvod*)malloc(n * sizeof(Proizvod));
	if (proizvodi != NULL)
	{
		for (int i = 0; i < n; i++)
		{
			scanf("%s%f%d%d", proizvodi[i].naziv, &proizvodi[i].cena, &proizvodi[i].kolicina_na_stanju, &proizvodi[i].kategorija);
		}

		SortirajPoCeni(proizvodi, n);
		float razlika = UkupnaVrednostRazlika(proizvodi, n);
		printf("%s %.2f %.2f", proizvodi[0].naziv, proizvodi[0].cena, razlika);
		free(proizvodi);
	}
}

