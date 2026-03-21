/*
16.1.26. Na programskom jeziku C napisati strukturni program koji se koristi za praćenje statistike na
Evropskom prvenstvu u vaterpolu. Za svaku reprezentaciju se čuva naziv (char ime[]), broj šuteva (int
sutevi), broj postignutih golova (int golovi) i broj osvojenih bodova (int bodovi). Napisati funkciju
najbolji_ucinak koja u nizu reprezentacija pronalazi i vraća reprezentaciju sa najboljim odnosom šuteva
na gol i postignutih golova. Napisati funkciju max_poena koja u nizu reprezentacija pronalazi i vraća
reprezentaciju sa najviše poena. U glavnom programu sa tastature učitati dinamički niz od N
reprezentacija, gde se N takođe unosi sa tastature. Nakon toga, neophodno je ispitati da li je reprezentacija
sa najboljim odnosom šuteva na gol i postignutih golova reprezentacija sa maksimalnim brojem osvojenih
bodova. Ukoliko jeste, na standardnom izlazu ispisati naziv te reprezentacije - u suprotnom ispisati
"FAIL".
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
	char ime[50];
	int sutevi;
	int golovi;
	int bodovi;
} Reprezentacija;
Reprezentacija najbolji_ucinak(Reprezentacija* rep, int n) {
	int i, indeks = 0;
	double najbolji_odnos = (double)rep[0].golovi / rep[0].sutevi;
	for (i = 1; i < n; i++) {
		double odnos = (double)rep[i].golovi / rep[i].sutevi;
		if (odnos > najbolji_odnos) {
			najbolji_odnos = odnos;
			indeks = i;
		}
	}
	return rep[indeks];
}
Reprezentacija max_poena(Reprezentacija* rep, int n) {
	int i, indeks = 0;
	for (i = 1; i < n; i++) {
		if (rep[i].bodovi > rep[indeks].bodovi) {
			indeks = i;
		}
	}
	return rep[indeks];
}
int main() {
	int N, i;
	Reprezentacija* rep;
	scanf("%d", &N);
	rep = (Reprezentacija*)malloc(N * sizeof(Reprezentacija));
	if (rep == NULL) {
		return 1;
	}
	for (i = 0; i < N; i++) {
		scanf("%s", rep[i].ime);
		scanf("%d %d %d", &rep[i].sutevi, &rep[i].golovi, &rep[i].bodovi);
	}
	Reprezentacija r1 = najbolji_ucinak(rep, N);
	Reprezentacija r2 = max_poena(rep, N);
	if (strcmp(r1.ime, r2.ime) == 0) {
		printf("%s\n", r1.ime);
	}
	else {
		printf("FAIL\n");
	}
	free(rep);
	return 0;
}
/*
12.11.25. Na programskom jeziku C napisati strukturni program kojim se vodi evidencija o video
igrama koje su dostupne u okviru prodavnice. Podatke o igrama potrebno je modelirati korišćenjem
strukture podataka Igra, koja je opisana uz pomoć sledećih elemenata: naziv (string bez razmaka), godina,
platforma (string bez razmaka — npr. “PC”, “PlayStation”, “Xbox” itd.), popularnost (realni broj od 1 do
5), cena (realan broj). Potrebno je implementirati sledeće funkcije: 1) TopIgra: Funkcija koja za zadatu
platformu i period (početna i krajnja godina) prikazuje najpopularniju video igru (po vrednosti atributa
popularnost) objavljenu u tom periodu. Ako postoji više od jedne, prikazati sve koje imaju istu vrednost
popularnosti. Ako nema nijedne, prikazati poruku: “Nema”. 2) ProsecnaCenaPlatforme: Funkcija koja
određuje prosečnu cenu svih igara za zadatu platformu. Ako ne postoji niti jedna igra za tu platformu,
vratiti 0 kao rezultat. U glavnom program dinamički kreirati niz od N igara, pri čemu korisnik unosi broj
igara i njihove podatke sa standardnog ulaza. Nakon unosa, korisnik unosi ime platforme i interval godina
(početnu i krajnju godinu). Na standardnom izlazu prikazati ishod poziva funkcije TopIgra, a zatim i
rezultat funkcije ProsecnaCenaPlatforme za istu platformu.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
	char naziv[50];
	int godina;
	char platforma[30];
	float popularnost;
	float cena;
} Igra;
void TopIgra(Igra* igre, int n, char* platforma, int godinaPoc, int godinaKraj) {
	float maxPopularnost = -1;
	int i, imaIgru = 0;
	for (i = 0; i < n; i++) {
		if (strcmp(igre[i].platforma, platforma) == 0 &&
			igre[i].godina >= godinaPoc && igre[i].godina <= godinaKraj) {
			if (igre[i].popularnost > maxPopularnost) {
				maxPopularnost = igre[i].popularnost;
				imaIgru = 1;
			}
		}
	}
	if (!imaIgru) {
		printf("Nema\n");
	}
	else {
		for (int i = 0; i < n; i++) {
			if (strcmp(igre[i].platforma, platforma) == 0 &&
				igre[i].godina >= godinaPoc && igre[i].godina <= godinaKraj &&
				igre[i].popularnost == maxPopularnost) {
				printf("%s %d %.2f %.2f\n",
					igre[i].naziv, igre[i].godina, igre[i].popularnost, igre[i].cena);
			}
		}
	}
}
float ProsecnaCenaPlatforme(Igra* igre, int n, char* platforma) {
	float rezultat = 0, suma = 0;
	int i, brojac = 0;
	for (i = 0; i < n; i++) {
		if (strcmp(igre[i].platforma, platforma) == 0) {
			suma += igre[i].cena;
			brojac++;
		}
	}
	if (brojac != 0)
		rezultat = suma / brojac;
	return rezultat;
}
int main() {
	int n, i;
	char platforma[30];
	int godinaPoc, godinaKraj;
	float prosek = 0;
	scanf("%d", &n);
	Igra* igre = (Igra*)malloc(n * sizeof(Igra));
	if (igre != NULL) {
		for (i = 0; i < n; i++) {
			scanf("%s", igre[i].naziv);
			scanf("%d", &igre[i].godina);
			scanf("%s", igre[i].platforma);
			scanf("%f", &igre[i].popularnost);
			scanf("%f", &igre[i].cena);
		}
		scanf("%s", platforma);
		scanf("%d", &godinaPoc);
		scanf("%d", &godinaKraj);
		TopIgra(igre, n, platforma, godinaPoc, godinaKraj);
		prosek = ProsecnaCenaPlatforme(igre, n, platforma);
		printf("%.2f\n", prosek);
		free(igre);
	}
	return 0;
}

/*
28.10.25. Na programskom jeziku C napisati strukturni program koji omogućava rad sa funkcijom.
Funkcija je data kao polinom od n članova i njen matematički zapis je prikazan u nastavku. Član je
predstavljen strukturom Clan koja sadrži stepen i koeficijent člana. Napisati funkciju Vrednost koja za
prosleđeni polinom i vrednost X računa i vraća rezultat funkcije. Napisati funkciju SortPoStepenu koja
sortira članove polinoma po stepenu u opadajući niz. Napisati i funkciju IzbaciNule koja treba da preuredi
polinom tako da ostanu samo oni članovi čiji koeficijent nije nula. Isključivo modifikovati postojeću
memoriju dodeljenu polinomu bez korišćenja pomoćnih nizova. U glavnom programu učitati jedan polinom
sa standardnog ulaza i vrednost X za koju treba odrediti vrednost funkcije. Zatim upotrebom napisanih
funkcija odrediti i prikazati vrednost funkcije za uneto X, sortirati polinom i prikazati nakon promene,
izbaciti nule iz polinoma i prikazati modifikovani polinom. Stepen i koeficijent prikazati korisniku
zaokruženu na 2 decimale. Članove polinoma razdvojiti znakom + (smatrati da su svi koeficijenti
nenegativni brojevi).
𝑓(𝑥) = ∑𝑘𝑖𝑥
𝑛−𝑖
𝑛
𝑖=0
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct Clan
{
	float Stepen;
	float Koeficijent;
} Clan;
float Vrednost(Clan polinom[], int n, float x)
{
	int i = 0;
	float f = 0;
	for (i = 0; i < n; i++)
		f += pow(x, polinom[i].Stepen) * polinom[i].Koeficijent;
	return f;
}
void SortPoStepenu(Clan polinom[], int n)
{
	int i, j, imax;
	Clan max;
	for (i = 0; i < n - 1; i++)
	{
		imax = i;
		for (j = i + 1; j < n; j++)
			if (polinom[j].Stepen > polinom[imax].Stepen)
				imax = j;
		if (i != imax)
		{
			max = polinom[i];
			polinom[i] = polinom[imax];
			polinom[imax] = max;
		}
	}
}
void IzbaciNule(Clan polinom[], int* n)
{
	int i = 0, j = 0;
	while (j < *n)
	{
		while (j < *n && polinom[j].Koeficijent == 0)
			j++;
		if (j < *n)
		{
			polinom[i] = polinom[j];
			i++;
			j++;
		}
	}
	*n = i;
}
void print(Clan polinom[], int n)
{
int i = 0;
for (i = 0; i < n-1; i++)
printf("%.2fX^%.2f + ", polinom[i].Koeficijent, polinom[i].Stepen);
if (n != 0)
printf("%.2fX^%.2f\n", polinom[n - 1].Koeficijent, polinom[n - 1].Stepen);}
int main()
{
Clan* polinom;
int i, n;
float x;
scanf("%d", &n);
polinom = (Clan*)malloc(n * sizeof(Clan));
for (i = 0; i < n; i++)
scanf("%f%f", &polinom[i].Stepen, &polinom[i].Koeficijent);
scanf("%f", &x);
print(polinom, n);
printf("%.2f\n", Vrednost(polinom, n, x));
SortPoStepenu(polinom, n);
print(polinom, n);
IzbaciNule(polinom, &n);
print(polinom, n);
free(polinom);
return 0;
}


/*
21.10.25. Na programskom jeziku C napisati strukturni program kojim se vodi evidencija o
putovanjima. Podatke o putovanjima je potrebno modelirati korišćenjem strukture podataka Putovanje,
koja sadrži sledeće elemente: destinacija (jedna reč), broj dana (ceo broj), cena aranžmana po osobi u
evrima (realan broj) i tip putovanja (karakter: 'L' za letovanje, 'Z' za zimovanje). Napisati funkciju
SortirajPoCeni koja sortira niz putovanja po ceni aranžmana u rastućem redosledu. Napisati funkciju
NajskupljeLetovanje koja pronalazi i vraća pokazivač na najskuplje letovanje duže od 7 dana (smatrati da
postoji bar jedno ovakvo letovanje među unetim putovanjima). U glavnom programu dinamički kreirati
niz od N putovanja, pri čemu broj putovanja i njihove podatke unosi korisnik sa standardnog ulaza.
Nakon unosa prikazati putovanja sortirana po ceni, pozivom funkcije SortirajPoCeni (elemente svakog
putovanja prikazati u posebnom redu, cenu aranžmana prikazati sa dve decimale). Konačno, u novom
redu prikazati naziv destinacije i cenu najskupljeg letovanja dobijenog pozivom funkcije
NajskupljeLetovanje.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	typedef struct {
		char destinacija[30];
		int brojDana;
		float cena;
		char tip;
	} Putovanje;
	void ZameniPutovanja(Putovanje * prvo, Putovanje * drugo) {
		Putovanje pom = *prvo;
		*prvo = *drugo;
		*drugo = pom;
	}
	void SortirajPoCeni(Putovanje * niz, int n) {
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < n - i - 1; j++) {
				if (niz[j].cena > niz[j + 1].cena)
					ZameniPutovanja(&niz[j], &niz[j + 1]);
			}
		}
	}
	Putovanje* NajskupljeLetovanje(Putovanje * niz, int n) {
		Putovanje* najskuplje = NULL;
		for (int i = 0; i < n; i++) {
			if (niz[i].tip == 'L') {
				if (najskuplje == NULL || (niz[i].cena > najskuplje->cena && niz[i].brojDana > 7))
				{
					najskuplje = &niz[i];
				}
			}
		}
		return najskuplje;
	}
	int main() {
		int n, i;
		scanf("%d", &n);
		Putovanje* putovanja = (Putovanje*)malloc(n * sizeof(Putovanje));
		if (putovanja != NULL) {
			for (i = 0; i < n; i++) {
				scanf("%s %d %f %c",
					putovanja[i].destinacija,
					&putovanja[i].brojDana,
					&putovanja[i].cena,
					&putovanja[i].tip);
			}
			SortirajPoCeni(putovanja, n);
			for (i = 0; i < n; i++) {
				printf("%s %d %.2f %c\n",
					putovanja[i].destinacija,
					putovanja[i].brojDana,
					putovanja[i].cena,
					putovanja[i].tip);
			}
			Putovanje* najleto = NajskupljeLetovanje(putovanja, n);
			printf("%s %.2f\n", najleto->destinacija, najleto->cena);
			free(putovanja);
		}
		return 0;
	}
