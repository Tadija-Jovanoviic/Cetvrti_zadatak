/*
Na programskom jeziku C napisati strukturni program koji upravlja transakcijama korisnika.
Za svaku transakciju se čuva iznos transakcije (unsigned int iznos) i tip transakcije (char tip - priliv novca
= 0, odliv novca = 1). Napisati funkciju saldo koja određuje razliku priliva i odliva novca korisnika. Napisati
funkciju preraspodela koja od prosleđenih transakcija kreira nove transakcije u dinamičkoj zoni memorije,
tako da se na početku novog niza nalaze transakcije tipa priliv, a u nastavku transakcije tipa odliv. U
glavnom programu učitati N transakcija i smestiti ih u dinamičku zonu memorije. Na ekranu prikazati saldo
korisnika, kao i transakcije korisnika nakon njihove preraspodele.
*/
#include <stdio.h>
#include <stdlib.h>
typedef struct {
	unsigned int iznos;
	char tip;
} Transakcija;
int saldo(Transakcija* transakcije, int n) {
	int saldo = 0;
	for (int i = 0; i < n; i++) {
		if (transakcije[i].tip == 0) {
			saldo += transakcije[i].iznos;
		}
		else {
			saldo -= transakcije[i].iznos;
		}
	}
	return saldo;
}
Transakcija* preraspodela(Transakcija* transakcije, int n) {
	Transakcija* noveTransakcije = (Transakcija*)malloc(n * sizeof(Transakcija));
	int brojacPriliv = 0;
	int brojacOdliv = n - 1;
	for (int i = 0; i < n; i++) {
		if (transakcije[i].tip == 0) {
			noveTransakcije[brojacPriliv] = transakcije[i];
			brojacPriliv++;
		}
		else {
			noveTransakcije[brojacOdliv] = transakcije[i];
			brojacOdliv--;
		}
	}
	return noveTransakcije;
}
void main() 
{
	int n;
	Transakcija* transakcije;
	Transakcija* transakcije_preraspodela;
	scanf("%d", &n);
	transakcije = (Transakcija*)malloc(n * sizeof(Transakcija));
	for (int i = 0; i < n; i++)
		scanf("%u %d", &transakcije[i].iznos, &transakcije[i].tip);
	printf("%d\n", saldo(transakcije, n));
	transakcije_preraspodela = preraspodela(transakcije, n);
	for (int i = 0; i < n; i++)
		printf("%u %d\n", transakcije_preraspodela[i].iznos,
			transakcije_preraspodela[i].tip);
	free(transakcije_preraspodela);
	free(transakcije);
}