#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX (100)


typedef struct stablo* Stablo;
typedef struct stablo {
	char* ime;
	Stablo child;
	Stablo sibling;

};

typedef struct stog* Stog;
struct stog {
	Stablo direktorij;
	Stog next;
	Stog prev;
};

int md(Stablo);
int direktorij(Stablo);
int putanja(Stog, Stablo, Stablo);
Stablo cd(Stablo, Stog);
Stablo nazad(Stablo, Stog);
Stablo naziv(Stablo, char*);
int push(Stog, Stablo);
Stablo pop(Stog);
Stog PronadiZadnjeg(Stog);
int Izbornik(Stablo, Stog);

int main()
{
	Stablo root;
	Stog head;
	int brojac = 0;

	root = (Stablo*)malloc(sizeof(struct stablo));
	root->child = NULL;
	root->sibling = NULL;

	head = (Stog*)malloc(sizeof(struct stog));
	head->next = NULL;
	head->prev = NULL;


	root->ime = (char*)malloc(MAX * sizeof(char));
	root->ime = "C:";

	do {
		brojac = Izbornik(root, head);
	} while (!brojac);

	return 0;
}

int md(Stablo current) {
	Stablo dir;
	dir = (Stablo)malloc(sizeof(Stablo));
	dir->ime = (char*)malloc(MAX * sizeof(char));

	if (current->child != NULL) {
		current = current->child;
		while (current->sibling != NULL)
			current = current->sibling;
		current->sibling = dir;
	}
	else
		current->child = dir;

	scanf(" %s", dir->ime);

	dir->child = NULL;
	dir->sibling = NULL;

	return 0;
}

int direktorij(Stablo current)
{
	if (current->child == NULL)
	{
		printf("Direktorij je prazan!\n");
		return 0;
	}

	current = current->child;

	printf("Direktoriji: \n");
	printf("-- %s\n", current->ime);

	while (current->sibling != NULL)
	{
		printf("-- %s\n", current->sibling->ime);
		current = current->sibling;
	}

	return 0;
}

int putanja(Stog head, Stablo root, Stablo current)
{
	Stog p = NULL;

	p = PronadiZadnjeg(head);

	printf("\n");

	if (head->next == NULL)
	{
		printf("%s>", root->ime);
		return EXIT_SUCCESS;
	}

	while (p->prev != NULL)
	{
		printf("%s>", p->direktorij->ime);
		p = p->prev;
	}

	printf("%s>", current->ime);

	return 0;
}

Stablo cd(Stablo current, Stog head)
{
	Stablo datoteka = NULL;
	char* imeDir = NULL;
	imeDir = (char*)malloc(MAX * sizeof(char));

	scanf(" %s", imeDir);

	if (current->child == NULL)
	{
		printf("Direktorij ne postoji!\n");
		return current;
	}

	datoteka = naziv(current, imeDir);
	push(head, current);

	return datoteka;
}

Stablo nazad(Stablo current, Stog head)
{
	Stablo datoteka;

	datoteka = pop(head);

	if (datoteka == NULL)
	{
		printf("ERROR!\n");
		datoteka = current;
	}

	return datoteka;
}

Stablo naziv(Stablo current, char* Ime)
{
	current = current->child;


	while (strcmp(Ime, current->ime) != 0 && current->sibling != NULL) {
		current = current->sibling;
	}

	if (current->sibling == NULL) {
		if (strcmp(Ime, current->ime) != 0)
			return 0;
		else
			return current;
	}

	else
		return current;

}

int push(Stog head, Stablo dir)
{
	Stog novi = (Stog)malloc(sizeof(struct stog));

	novi->next = head->next;
	novi->prev = head;
	if (head->next != NULL)
		head->next->prev = novi;
	head->next = novi;
	novi->direktorij = dir;

	return 0;
}

Stablo pop(Stog head) {

	Stog p = (Stog)malloc(sizeof(Stog));

	Stablo p1 = NULL;

	if (head->next == NULL)
		return 0;

	p = head->next;
	p1 = p->direktorij;
	head->next = head->next->next;

	if (head->next != NULL)
		head->next->prev = head;
	free(p);

	return p1;
}

Stog PronadiZadnjeg(Stog head)
{
	Stog pok;

	pok = head->next;

	if (pok == NULL)
		return NULL;

	while (pok->next != NULL)
		pok = pok->next;

	return pok;
}

int Izbornik(Stablo root, Stog head)
{
	Stablo current = root;
	char unos[MAX] = { 0 };

	printf("---------------------------------------\n");
	printf("md \n");
	printf("cd \n");
	printf("cd.. \n");
	printf("dir \n");
	printf("exit \n");

	while (1)
	{
		putanja(head, root, current);
		scanf(" %s", unos);


		if (!strcmp(unos, "md"))
			md(current);

		else if (!strcmp(unos, "cd"))
			current = cd(current, head);

		else if (!strcmp(unos, "cd.."))
			current = nazad(current, head);

		else if (!strcmp(unos, "dir"))
			direktorij(current);


		else if (!strcmp(unos, "exit"))
			return 1;


		else if (!strcmp(unos, "izbornik"))
			return 0;

		else
			printf("Naredba nije pronadena!\n");
	}

	return 0;
}
