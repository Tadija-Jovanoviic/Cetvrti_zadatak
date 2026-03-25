/*
Na programskom jeziku C napisati strukturni program kojim se vodi evidencija o studentima na
fakultetu. Podatke o studentima je potrebno modelirati koriscenjem strukture podataka Student,
koja je opisana koriscenjem: imena, prezimena, prosecne ocene (realan broj), broja polozenih
ispita (ceo broj) i nacina finansiranja (budzet = 1, samofinansiranje = 0). Napisati funkciju
SortirajPoProseku za sortiranje niza studenata u opadajuci redosled po prosecnoj oceni.
Napisati funkciju ProsecnaOcenaRazlika koja racuna razliku izmedju prosecne ocene budzetskih
studenata i prosecne ocene samofinansirajucih studenata (smatrati da postoji makar jedan
student svake kategorije). U glavnom programu dinamicki kreirati niz od N studenata, pri cemu
broj studenata i same studente unosi korisnik sa standardnog ulaza. Na standardnom izlazu
prikazati ime i prezime studenta sa najboljim prosekom (koriscenjem funkcije SortirajPoProseku),
a potom u nastavku ispisati razliku prosecnih ocena.
*/
#include<stdio.h>
#include<stdlib.h>
typedef struct {
	char ime[20];
	char prezime[30];
	float prosecna_ocena;
	int polozeni_ispiti;
	int budzet; // 1 = budzet, 0 = samofinansiranje
} Student;
void ZamenaMesta(Student* prviStudent, Student* drugiStudent)
{
	Student pom = *prviStudent;
	*prviStudent = *drugiStudent;
	*drugiStudent = pom;
}

void SortirajPoProseku(Student* studenti, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (studenti[j].prosecna_ocena > studenti[i].prosecna_ocena)
			{
				ZamenaMesta(&studenti[i], &studenti[j]);
			}
		}
	}
}

float ProsecnaOcenaRazlika(Student* studenti, int n)
{
	float ukupna_ocena_budzet = 0, ukupna_ocena_samofinansiranje = 0;
	int broj_budzet = 0, broj_samo = 0;
	for (int i = 0; i < n; i++)
	{
		if (studenti[i].budzet == 1)
		{
			ukupna_ocena_budzet += studenti[i].prosecna_ocena;
			broj_budzet++;
		}
		else
		{
			ukupna_ocena_samofinansiranje += studenti[i].prosecna_ocena;
			broj_samo++;
		}
	}
	float prosecna_ocena_budzet = ukupna_ocena_budzet / broj_budzet;
	float prosecna_ocena_samofinansiranje = ukupna_ocena_samofinansiranje / broj_samo;

	return prosecna_ocena_budzet - prosecna_ocena_samofinansiranje;
}

int main()
{
	Student* studenti;
	int n;
	scanf("%d", &n);
	studenti = (Student*)malloc(n * sizeof(Student));
	if (studenti != NULL)
	{
		for (int i = 0; i < n; i++)
		{
			scanf("%s%s%f%d%d", studenti[i].ime, studenti[i].prezime,
				&studenti[i].prosecna_ocena, &studenti[i].polozeni_ispiti,
				&studenti[i].budzet);
		}
		SortirajPoProseku(studenti, n);
		float razlika = ProsecnaOcenaRazlika(studenti, n);
		printf("%s %s %.2f", studenti[0].ime, studenti[0].prezime, razlika);
		free(studenti);
	}
}
