#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)
#define MAX_BODOVI (20)

typedef struct {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int bodovi;
}student;

int BrojStudenata(char* ime_datoteke);
student* Alokacija(int br_st,char* ime_datoteke);
student MaxBodovi(student* studenti,int br_st);
void Ispis(int br_st,student* studenti);


int main()
{
	char* studenti = NULL;
	int brojac = 0;
	int br_st = 0;
	student* stud = NULL;
	student s;

	br_st = BrojStudenata(studenti);
	stud = Alokacija(br_st, studenti);
	s = MaxBodovi(stud,br_st);

	Ispis(br_st,stud);
	

	return EXIT_SUCCESS;
}


int BrojStudenata(char* ime_datoteke)
{
	char BUFFER[MAX_LINE] = { 0 };
	FILE* datoteka = NULL;
	int brojac = 0;
	datoteka = fopen("studenti.txt","r");

	if (!datoteka)
	{
		printf("Datoteka nije otovorena!");
		return;
	}

	while (!feof(datoteka)) {
		fgets(BUFFER,MAX_LINE,datoteka);
		brojac++;
	}
	fclose(datoteka);


	return brojac;
}

student* Alokacija(int br_st, char* ime_datoteke)
{
	int brojac=0;
	student* studenti = NULL;
	FILE* datoteka = NULL;
	datoteka = fopen("studenti.txt","r");
	studenti = (student*)malloc(br_st * (sizeof(student)));	

	if (!datoteka)
	{
		printf("Datoteka nije otvorena!");
		return NULL;
	}
	if (!studenti)
	{
		printf("Greska alociranja!");
		return NULL;
	}

	while (!feof(datoteka))
	{
		fscanf(datoteka," %s %s %lf",studenti[brojac].ime,studenti[brojac].prezime,&studenti[brojac].bodovi);
		brojac++;
	}

	fclose(datoteka);


	return studenti;
}

student MaxBodovi(student* studenti, int br_st)
{
	student temp = { 0 };
	int i = 0;

	temp = studenti[0];
	for (i=1; i < br_st; i++) 
	{
		if (temp.bodovi < studenti[i].bodovi)
			temp = studenti[i];
	}

	return temp;
}

void Ispis(int br_st, student* studenti)
{
	int i = 0;
	double relativni = 0;



	while (i < br_st)
	{
		relativni = (studenti[i].bodovi / MAX_BODOVI) * 100;
		printf("\nIme: %s \nPrezime: %s \nApsolutni broj bodova: %.2lf \nRelativni broj bodova: %.2lf \n\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativni);
		i++;
	}

}



