#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
	char ime[15];
	char prezime[15];
	int bodovi;
}Stud;

int brojRedaka(const char *imeDatoteke);
Stud* ucitajStudente(const char* imeDatoteke, int brojStudenata);
int maxBodovi(Stud *studenti,int brojStudenata);
void ispisPodataka(Stud *studenti, int brojStudenata, int najBodova);

int main() {
	
	int brojStudenata = 0;
	char imeDatoteke[50];
	
	printf("Unesi ime datoteke: ");
	scanf("%s", imeDatoteke);
	
	brojStudenata=brojRedaka(imeDatoteke);							//prva funckija, brojanje redaka

	printf("U datoteci je zapisano %d studenta.\n", brojStudenata);

	Stud* studenti = ucitajStudente(imeDatoteke, brojStudenata);	//druga funckija, ucitava sve podatke i alocira memoriju za niz struktura
	
	
	int najBodova = maxBodovi(studenti, brojStudenata);				//treca funkcija, pronalazi najveci broj bodova na kolokviju
	
	ispisPodataka(studenti, brojStudenata, najBodova);				//cetvrta funckija, ispis podataka i racunanje relativnog broja bodova
	
	
	free(studenti); 

	return 0;
}

int brojRedaka(const char *imeDatoteke){
	FILE* fp = fopen(imeDatoteke,"r");
	
	int broj=0;
	char buffer[50];
	while (fgets(buffer, 50, fp))
		broj++;

	fclose(fp);

	return broj;
}

Stud* ucitajStudente(const char* imeDatoteke, int brojStudenata) {
	int i;
	FILE* fp = fopen(imeDatoteke,"r");
	Stud* studenti = (Stud*)malloc(brojStudenata * sizeof(Stud));

	for (i = 0; i < brojStudenata; i++) {
		fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
	}

	fclose(fp);

	return studenti;
}

int maxBodovi(Stud* studenti, int brojStudenata) {
	int max = studenti[0].bodovi;
	int i;
	for (i = 1; i < brojStudenata; i++) {
		if (studenti[i].bodovi > max)
			max = studenti[i].bodovi;
	}
	return max;
}

void ispisPodataka(Stud* studenti, int brojStudenata, int najBodova) {

	for (int i = 0; i < brojStudenata; i++) {
		double relativni = ((double)studenti[i].bodovi / najBodova) * 100.0;
		printf("%-15s %-15s %-10d %-15.2f\n",
			studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativni);
	}
}