#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)//za windows max line
#define MAX_BODOVI (20)


typedef struct _student{
	char ime [MAX_SIZE];
	char prezime [MAX_SIZE];
	double bodovi;
}student;

int procitajBrojRedakaIzDatoteke(char* nazivDatoteke);
student* alocirajProcitajIzDatoteke(int brojStudenata, char*nazivDatoteke);
student najveciBrojBodova(student* studenti, int BrojStudenata);
void ispisStudenata(int BrojStudenata, char* nazivDatoteka);

int main()
{
	char* studenti = NULL;
	int br_st = 0;
	int brojac = 0;
	student* stud = NULL;
	student s = {0};

	br_st = procitajBrojRedakaIzDatoteke(studenti);
	stud = alocirajProcitajIzDatoteke(br_st, studenti);
	s = najveciBrojBodova(stud, br_st);
	ispisStudenata(br_st, studenti);

	
	return 0;
}

int procitajBrojRedakaIzDatoteke(char* nazivDatoteke)
{
	int brojac = 0;
	FILE* datoteka = NULL;//sve datoteke moraju bit inicijalizirane,makar na nulu
	char buffer[MAX_LINE] = {0};//niz je pa je {0}


	datoteka = fopen(nazivDatoteke, "r");

	if (!datoteka)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return -1;
	}

	while (!feof(datoteka))
	{
		fgets(buffer, MAX_LINE, datoteka);
		brojac++;
	}

	fclose(datoteka);//obavezno zatvaranje 
	return brojac;


}

student* alocirajProcitajIzDatoteke(int brojStudenata, char* nazivDatoteke)
{
	int brojac = 0;
	FILE* datoteka = NULL;
	student* studenti = NULL;

	studenti = (student*)malloc(brojStudenata * sizeof(student));
	
	if (!datoteka)
	{
		printf("Neuspjesna alokacija memorije");
		return NULL;
	}


	datoteka = fopen(nazivDatoteke, "r");

	if (!datoteka)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return 0;
	}


	while (!feof(datoteka))
	{
		fscanf(datoteka, " %s %s %lf", //gap ispred prvog %s,da se ne pokupi enter (umjesto fflush(stdin))
			studenti[brojac].ime,
			studenti[brojac].prezime,
			&studenti[brojac].bodovi);
		brojac++;
	}

	fclose(datoteka);

	return studenti;

}

student najveciBrojBodova(student* studenti, int BrojStudenata)
{
	int brojac = 0;
	student temp = { 0 };

	temp = studenti[0];
	for (brojac = 1; brojac < BrojStudenata; brojac++)
		if (temp.bodovi < studenti[brojac].bodovi)
			temp = studenti[brojac];

	return temp;

}

void ispisStudenata(int BrojStudenata, char* nazivDatoteka)
{
	int brojac = 0;
	student* stud = NULL;
	student s = { 0 };


	printf("Ime i Prezime\tApsolutan broj bodova\tRelativan broj bodova\n\n");

	for (brojac; brojac < BrojStudenata; brojac++)
	{
		printf("%s\t%s\t%.2lf%\t%.2lf\n", 
			stud[brojac].ime, 
			stud[brojac].prezime, 
			stud[brojac].bodovi / MAX_BODOVI * 100, 
			(stud[brojac].bodovi / s.bodovi) * 100);
	}


	return;
}



