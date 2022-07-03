#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)
#define MAX_LINE (1024)

typedef struct _Person;
typedef struct _Person* Pozicija;
typedef struct _Person {
	char* name[MAX_SIZE];
	char* surname[MAX_SIZE];
	int birthYear;
	Pozicija next;
}Person;

int ReadFromFile(Pozicija head, char* filename);
Pozicija CreatePerson(char* name, char* surname, int birthYear);
int SortList(Pozicija head,Pozicija newPerson);
int InsertAfter(Pozicija head,Pozicija newPerson);
int PrintList(Pozicija first);
int AddEl(Pozicija head,int  n);
Pozicija FindBefore(Pozicija head,int n);
int WriteInFile(Pozicija head,char* filename);
int FreeAll(Pozicija head);

int main()
{
	Person zeroth = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Pozicija head = &zeroth;
	char filename[MAX_SIZE] = { 0 };
	int n = 0;


	printf("From what file you want to read data:\n");
	scanf(" %s", filename);
	ReadFromFile(head, filename);

	printf("Ispis nakon sortiranja:\n\n");
	PrintList(head->next);

	printf("\nNakon kojeg elementa zelite dodati element:");
	scanf("%d",&n);
	AddEl(head,n);

	printf("\nIspis nakon umetanja nakon:\n");
	PrintList(head->next);


	printf("\nIspred kojeg elementa zelite dodati element:");
	scanf("%d", &n);
	AddEl(head, n-1);

	printf("\nIspis nakon umetanja ispred:\n");
	PrintList(head->next);


	printf("Ime datoteke u koju zelite upisati:\n");
	scanf(" %s", filename);
	WriteInFile(head->next, filename);

	printf("\nUSPJESAN UPIS U DATOTEKU!\n");

	FreeAll(head);
	printf("\nUspjesno brisanje memorije\n");

	

	
	return EXIT_SUCCESS;
}

int ReadFromFile(Pozicija head, char* filename)
{
	Pozicija newPerson = NULL;
	char* name[MAX_SIZE] = { 0 };
	char* surname[MAX_SIZE] = { 0 };
	int birthYear = 0;
	char* BUFFER[MAX_SIZE] = { 0 };

	FILE* fp = NULL;
	fp = fopen(filename, "r");

	if (!fp)
	{
		printf("Datoteka nije otvorena!\n");
		return -1;
	}

	while (!feof(fp))
	{
		fgets(BUFFER, MAX_LINE, fp);
		if (sscanf(BUFFER, " %s %s %d", name, surname, &birthYear) == 3)
		{
			newPerson = CreatePerson(name, surname, birthYear);
			SortList(head, newPerson);
		}

	}
	fclose(fp);


	return EXIT_SUCCESS;
}

Pozicija CreatePerson(char* name, char* surname, int birthYear)
{
	Pozicija newPerson = NULL;

	newPerson = (Pozicija)malloc(sizeof(Person));

	if (!newPerson)
	{
		perror("Allocation error!\n");
		return NULL;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;


	return newPerson;
}


int SortList(Pozicija head, Pozicija newPerson)
{
	Pozicija temp = head->next;

	if (!temp)
	{
		InsertAfter(head, newPerson);
	}

	else if (temp->next)
	{
		if (strcmp(newPerson->surname, temp->surname) >= 0)
		{
			while (temp->next)
			{
				if (strcmp(newPerson->surname, temp->surname) >= 0 && strcmp(newPerson->surname, temp->next->surname) < 0)
				{
					InsertAfter(temp, newPerson);
					return EXIT_SUCCESS;
				}
				temp = temp->next;
			}
			if (!temp->next)
			{
				InsertAfter(temp, newPerson);
			}
		}
		else
		{
			InsertAfter(head, newPerson);
		}

	}


	else
	{
		if (strcmp(newPerson->surname, temp->surname) >= 0)
		{
			InsertAfter(temp, newPerson);
		}
		else
		{
			InsertAfter(head, newPerson);
		}
	}


	return EXIT_SUCCESS;
}



int InsertAfter(Pozicija head, Pozicija newPerson)
{
	newPerson->next = head->next;
	head->next = newPerson;

	return EXIT_SUCCESS;
}

int PrintList(Pozicija first)
{
	Pozicija temp = first;

	while (temp)
	{


		printf("IME: %s\n", temp->name);
		printf("PREZIME: %s\n", temp->surname);
		printf("GODINA RODENJA: %d\n\n", temp->birthYear);


		temp = temp->next;

	}


	return EXIT_SUCCESS;
}

int AddEl(Pozicija head, int n)
{
	Pozicija newPerson = NULL;
	Pozicija personBefore = NULL;
	char* ime[MAX_SIZE] = { 0 };
	char* prezime[MAX_SIZE] = { 0 };
	int godine = 0;

	printf("Unesite podatke:\n");
	printf("IME:");
	scanf(" %s",ime);
	printf("PREZIME:");
	scanf(" %s", prezime);
	printf("GODINE:");
	scanf(" %d", &godine);

	personBefore = FindBefore(head,n);

	newPerson = CreatePerson(ime,prezime,godine);

	InsertAfter(personBefore,newPerson);




	return EXIT_SUCCESS;
}

Pozicija FindBefore(Pozicija head, int n)
{
	Pozicija temp = head;

	while (n)
	{
		temp = temp->next;
		n--;
	}

	
	return temp;
}


int WriteInFile(Pozicija head, char* filename)
{
	Pozicija temp = head;
	FILE* fp = NULL;
	fp = fopen(filename,"w");

	if (!fp)
	{
		printf("Nemoguce otvoriti datoteku.");
		return NULL;
	}

	while (temp)
	{
		fprintf(fp," IME:%s\tPREZIME:%s\tGODINE:%d\n",temp->name,temp->surname,temp->birthYear);
		temp = temp->next;
	}
	fclose(fp);


	return EXIT_SUCCESS;
}

int FreeAll(Pozicija head)
{
	Pozicija temp1 = head;
	Pozicija temp2 = NULL;

	while (temp1->next)
	{
		temp2 = temp1->next;
		temp1->next = temp2->next;
		free(temp2);
	}

	return EXIT_SUCCESS;
}















