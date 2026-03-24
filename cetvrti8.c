/* 30.8.25.
Na programskom jeziku C napisati strukturni program kojim se vodi evidencija o teniserima
na ATP turu. Informacije o teniserima je potrebno modelirati korišćenjem strukture podataka Teniser sa
elementima: ime, prezime, rang (ceo broj), osvojeni nagradni fond u tekućoj sezoni i specijalnost (za singl
igrače vrednost je postavljena na 1, dok je za dubl igrače 0). Napisati funkciju GrupišiPoRangu koja vrši
grupisanje igrača, tako da na početak niza najpre stavlja igrače rangirane ispod određene granice (smatrati
da postoji makar jedan takav teniser), a potom u nastavku i preostale igrače. Potrebno je očuvati inicijalni
redosled igrača koji su rangirani ispod granice. Napisati funkciju MinMaxRazlika koja određuje razliku u
zaradi između najplaćenijeg singl igrača i najmanje plaćenog dubl igrača.
U glavnom programu dinamički kreirati niz od M tenisera, pri čemu broj tenisera, ali i same tenisere unosi
korisnik sa standardnog ulaza, dok je granicu ranga potrebno definisati kao konstantu sa vrednošću 30. Na
standardnom izlazu prikazati ime i prezime prvog igrača dobijenog pozivom fukcije GrupišiPoRangu, a
potom u nastavku prikazati razliku u zaradi.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define granica 30
typedef struct {
	char ime[20];
	char prezime[20];
	int rang;
	int nagradni_fond;
	int specijalnost;
} Teniser;
void ZameniTenisere(Teniser* prvi, Teniser* drugi)
{
	Teniser pom = *prvi;
	*prvi = *drugi;
	*drugi = pom;
}
void GrupisiPoRangu(Teniser* teniseri, int brojTenisera)
{
	int trenutni = 0;
	for (int i = 0; i < brojTenisera; i++)
	{
		if (teniseri[i].rang < granica)
		{
			ZameniTenisere(&teniseri[i], &teniseri[trenutni]);
			trenutni++;
		}
	}
}
int MinMaxRazlika(Teniser teniseri[], int brojTenisera)
{
	int max = 0, min = INT_MAX;
	for (int i = 0; i < brojTenisera; i++)
	{
		if (teniseri[i].nagradni_fond > max && teniseri[i].specijalnost == 1)
		{
			max = teniseri[i].nagradni_fond;
		}
		if (teniseri[i].nagradni_fond < min && teniseri[i].specijalnost == 0)
		{
			min = teniseri[i].nagradni_fond;
		}
	}
	int razlika = abs(max - min);
	return razlika;
}
int main()
{
	Teniser* teniseri;
	int m;
	scanf("%d", &m);
		teniseri = (Teniser*)malloc(m * sizeof(Teniser));
	if (teniseri != NULL)
	{
		for (int i = 0; i < m; i++)
		{
			scanf("%s%s%d%d%d", teniseri[i].ime, teniseri[i].prezime,
				&teniseri[i].rang, &teniseri[i].nagradni_fond, &teniseri[i].specijalnost);
		}
		GrupisiPoRangu(teniseri, m);
		int min_max = MinMaxRazlika(teniseri, m);
		printf("%s %s %d", teniseri[0].ime, teniseri[0].prezime, min_max);
		free(teniseri);
	}
}