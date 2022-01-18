#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int godine;
	Position next;
}Person;

int PrependList(Position head, char* ime, char* prezime, int godine);
Position CreatePerson(char* ime, char* prezime, int godine);
int InsertAfter(Position head, Position newPerson);
int PrintList(Position head);
int AppendList(Position head, char* ime, char* prezime, int godine);
Position FindLast(Position head);
Position FindBySurname(Position head, char* prezime);
int DeleteAfter(Position head,int n);
Position FindPrevious(Position head, int poz);
int DeleteAll(Position head);


int main(int argc, char** argv)
{
	Person zeroth = { .next = NULL, .ime = { 0 }, .prezime = {0}, .godine = 0 };
	Position head = &zeroth;
	int br_osoba=0, godine=0;
	char ime[MAX_SIZE] = { 0 }, prezime[MAX_SIZE] = { 0 };
	Position surname = NULL;

	printf("Koliko osoba zelite unijeti na pocetku:");
	scanf(" %d",&br_osoba);
	printf("Upisite osobe:\n");

	while (br_osoba)
	{
		printf("Ime:");
		scanf(" %s", ime);
		printf("Prezime:");
		scanf(" %s", prezime);
		printf("Godina rodenja:");
		scanf(" %d",&godine);
		PrependList(head,ime,prezime,godine);
		br_osoba--;
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Ispis osoba nakon dodavanja na pocetku:\n");
	PrintList(head->next);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");



	printf("Koliko osoba zelite unijeti na kraj:");
	scanf(" %d", &br_osoba);
	printf("Upisite osobe:\n");

	while (br_osoba)
	{
		printf("Ime:");
		scanf(" %s", ime);
		printf("Prezime:");
		scanf(" %s", prezime);
		printf("Godina rodenja:");
		scanf(" %d", &godine);
		AppendList(head, ime, prezime, godine);
		br_osoba--;
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Ispis osoba nakon dodavanja na kraj:\n");
	PrintList(head->next);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");


	printf("Unesite prezime osobe koju zelite naci:");
	scanf(" %s", prezime);
	surname = FindBySurname(head->next,prezime);

	if (!surname)
	{
		printf("Osoba ne postoji!");
	}
	else
	{
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("Ime:%s	Prezime:%s	Godina rodjena:%d\n", surname->ime, surname->prezime,surname->godine);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	
	}

	printf("Koji element zelite izbrisati iz vezane liste:");
	scanf(" %d",&br_osoba);
	DeleteAfter(head,br_osoba);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Ispis nakon brisanja:\n");
	PrintList(head->next);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	DeleteAll(head);


	return EXIT_SUCCESS;
}

int PrependList(Position head, char* ime, char* prezime, int godine)
{
	Position newPerson = NULL;

	newPerson = CreatePerson(ime,prezime,godine);

	if (!newPerson)
	{
		return -1;
	}

	InsertAfter(head,newPerson);



	return EXIT_SUCCESS;
}

Position CreatePerson(char* ime, char* prezime, int godine)
{
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson)
	{
		perror("Allocation ERROR!");
		return NULL;
	}

	strcpy(newPerson->ime,ime);
	strcpy(newPerson->prezime,prezime);
	newPerson->godine = godine;
	newPerson->next = NULL;

	return newPerson;
}

int InsertAfter(Position head, Position newPerson)
{
	newPerson->next = head->next;
	head->next = newPerson;


	return EXIT_SUCCESS;
}

int PrintList(Position head)
{
	Position temp = head;

	while (temp)
	{
		printf("Ime:%s	Prezime:%s	Godina rodjena:%d\n",temp->ime,temp->prezime,temp->godine);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int AppendList(Position head, char* ime, char* prezime, int godine)
{
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = CreatePerson(ime, prezime, godine);

	if (!newPerson)
	{
		return -1;
	}
	last = FindLast(head);

	InsertAfter(last, newPerson);

	return EXIT_SUCCESS;
}

Position FindLast(Position head)
{
	Position temp = head;

	while (temp->next)
	{
		temp = temp->next;
	}


	return temp;
}

Position FindBySurname(Position head, char* prezime)
{
	Position temp = head;
	
	while (temp)
	{
		if (strcmp(temp->prezime, prezime) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}


	return temp;
}

int DeleteAfter(Position head, int n)
{
	Position temp1 = FindPrevious(head,n-1);
	Position temp2 = NULL;

	if (!temp1)
	{
		printf("Taj element ne postoji!");

	}
	else
	{
		temp2 = temp1 -> next;
		temp1->next = temp2->next;
		free(temp2);
	}
	return EXIT_SUCCESS;
}

Position FindPrevious(Position head, int poz)
{
	Position temp = head;

	while (poz)
	{
		temp = temp->next;
		if (!temp->next)
		{
			return NULL;
		}
		poz--;
	}



	return temp;
}

int DeleteAll(Position head)
{
	Position temp1 = head;
	Position temp2 = NULL;

	while (temp1->next)
	{
		temp2 = temp1->next;
		temp1->next = temp2->next;
		free(temp2);
	}


	return EXIT_SUCCESS;
}







