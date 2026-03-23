/*
Na programskom jeziku C napisati strukturni program kojim se vodi evidencija o knjigama
koje su dostupne u okviru knjižare. Podatke o knjigama je potrebno modelirati korišćenjem strukture
podataka Knjiga, koja je opisana uz pomoć naziva knjige (smatrati da se naziv nalazi u okviru jedinstvene
reči), cene, broja stranica, kao i godine izdavanja. Napisati funkciju PoredjajKnjige koja vrši sortiranje
knjiga u rastući ili opadajući redosled, u zavisnosti od vrednosti prosleđenog smera (0 za rastući, 1 za
opadajući). Kao kriterijum za sortiranje koristiti broj stranica. Napisati funkciju ProsecneCene koja
određuje prosečnu cenu knjiga koje imaju trocifreni broj stranica i objavljene su u tekućoj godini (smatrati
da postoji makar jedna takva knjiga). U glavnom programu dinamički kreirati niz od N knjiga, pri čemu
broj knjiga, kao i same knjige unosi korisnik sa standardnog ulaza. Na standardnom izlazu prikazati naziv
i godinu izdavanja knjige sa najvećim brojem stranica, a potom i rezultat funkcije ProsecneCene.
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
typedef struct {
	char naziv[20];
	int cena;
	int broj_stranica;
	int godina_izdavanja;
}Knjiga;
void ZameniKnjige(Knjiga* prvaKnjiga, Knjiga* drugaKnjiga)
{
	Knjiga pom = *prvaKnjiga;
	*prvaKnjiga = *drugaKnjiga;
	*drugaKnjiga = pom;
}
void PoredjajKnjige(Knjiga* knjige, int brojKnjiga, int smer)
{
	for (int i = 0; i < brojKnjiga - 1; i++)
		for (int j = i + 1; j < brojKnjiga; j++)
			if ((smer == 0 && knjige[j].broj_stranica < knjige[i].broj_stranica) || (smer == 1 && knjige[j].broj_stranica > knjige[i].broj_stranica))
			{
				ZameniKnjige(&knjige[j], &knjige[i]);
			}
}
float ProsecneCene(Knjiga knjige[], int brojKnjiga)
{
	int br_knjiga_uslov = 0;
	int ukupna_cena = 0;
	for (int i = 0; i < brojKnjiga; i++)
	{
		if (knjige[i].broj_stranica > 100 && knjige[i].broj_stranica < 1000 && knjige[i].godina_izdavanja == 2026)
		{
			ukupna_cena += knjige[i].cena;
			br_knjiga_uslov++;
		}
	}
	float prosek = (float)ukupna_cena / br_knjiga_uslov;
	return prosek;
}
int main()
{
	Knjiga* knjige;
	int n;
	scanf("%d, &n");
	knjige = (Knjiga*)malloc(n * sizeof(Knjiga));
	if (knjige != NULL)
	{
		for (int i = 0; i < n; i++)
		{
			scanf("%s%d%d%d", knjige[i].naziv, &knjige[i].cena, &knjige[i].broj_stranica, &knjige[i].godina_izdavanja);
		}
		PoredjajKnjige(knjige, n, 1);
		float prosecna_cena = Prosecnecene(knjige, n);
		printf("%s %d %.2f\n", knjige[0].naziv, knjige[0].godina_izdavanja, prosecna_cena);
		free(knjige);
	}
	return 0;
}

