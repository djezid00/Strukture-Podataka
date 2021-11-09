#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50
#define MAX_LINE 1024

struct element;
typedef struct element* pozicija;
typedef struct element
{
	int koef;
	int exp;
	pozicija next;
}element;

int imeDatoteke(char* fileName);
int ucitajDatoteku(pozicija head1, pozicija head2, char* fileName);
int procitajRedak(pozicija head, char* buffer);
pozicija stvoriEL(int koef, int exp);
int sortirano(pozicija head, pozicija noviElement);
int merge(pozicija poz, pozicija noviElement);
int umetniNakon(pozicija position, pozicija noviElement);
int izbrisi(pozicija previous);
int zbroji(pozicija head1, pozicija head2, pozicija suma);
int pomnozi(pozicija umnozak, pozicija head1, pozicija head2);


int main()
{
	element head1 = { .koef = 0, .exp = 0, .next = NULL };
	element head2 = { .koef = 0, .exp = 0, .next = NULL };
	element suma = { .koef = 0, .exp = 0, .next = NULL };
	element umnozak = { .koef = 0, .exp = 0, .next = NULL };
	char fileName[MAX_SIZE] = { 0 };

	imeDatoteke(fileName);
	ucitajDatoteku(&head1, &head2, fileName);
	zbroji(&head1, &head2, &suma);
	pomnozi(&head1, &head2, &umnozak);


	return 0;
}

int imeDatoteke(fileName)
{
	printf("Unesite ime datoteke:");
	scanf(" %s", fileName);

	return 0;
}

int ucitajDatoteku(pozicija head1, pozicija head2, char* fileName)
{
	FILE* fp = NULL;
	fp = fopen(fileName, "r");

	int buffer[MAX_LINE] = { 0 };


	if (!fp)
	{
		printf("Datoteka nije pronađena!");
		return -1;
	}

	fgets(buffer, MAX_LINE, fileName);
	procitajRedak(head1, buffer);

	fgets(buffer, MAX_LINE, fileName);
	procitajRedak(head2, buffer);

	fclose(fp);

	return 0;
}

int procitajRedak(pozicija head, char* buffer)
{
	char* currentBuffer = buffer;
	int koef = 0;
	int exp = 0;
	int bytes = 0;
	pozicija noviElement = NULL;

	while (strlen(currentBuffer) > 0)
	{
		sscanf(currentBuffer, " %d %d %n", &koef, &exp, &bytes);


		noviElement = stvoriEl(koef, exp);
		sortirano(head, noviElement);
		currentBuffer += bytes;
	}

	return 0;
}

pozicija stvoriEl(int koef, int exp)
{
	pozicija node = NULL;
	node = (pozicija*)malloc(sizeof(pozicija));

	if (!node)
	{
		printf("Greska alokacije!\n");
		return;
	}

	node->koef = koef;
	node->exp = exp;
	node->next = NULL;


	return node;
}

int sortirano(pozicija head, pozicija noviElement)
{
	pozicija temp = head;

	while (temp->next != NULL && temp->next->exp < noviElement->exp)
	{
		temp = temp->next;
	}

	merge(temp, noviElement);

	return 0;
}
int merge(pozicija poz, pozicija noviElement)
{
	int rezKoef = 0;
	if (poz->next == NULL || poz->next->exp != poz->exp)
	{
		umetniNakon(poz, noviElement);
	}
	else
	{
		rezKoef = poz->next->koef + noviElement->koef;
		if (rezKoef == 0)
		{
			izbrisi(poz);
		}
		else
		{
			poz->next->koef = rezKoef;
		}
		free(noviElement);
	}

	return 0;
}
int umetniNakon(pozicija position, pozicija noviElement)
{
	noviElement->next = position->next;
	position->next = noviElement;

	return 0;
}


int izbrisi(pozicija previous)
{
	pozicija delete = NULL;

	delete = previous->next;
	previous->next = delete->next;
	free(delete);

	return 0;
}


int zbroji(pozicija head1, pozicija head2, pozicija suma)
{
	while (head1->next && head2->next) {

		if (head1->exp > head2->exp) {
			suma->exp = head1->exp;
			suma->koef = head1->koef;
			head1 = head1->next;
		}


		else if (head1->exp < head2->exp) {
			suma->exp = head2->exp;
			suma->koef = head2->koef;
			head2 = head2->next;
		}


		else {
			suma->exp = head1->exp;
			suma->koef = head1->koef + head2->koef;
			head1 = head1->next;
			head2 = head2->next;
		}


		suma->next = (pozicija*)malloc(sizeof(pozicija));
		suma = suma->next;
		suma->next = NULL;
	}
	while (head1->next || head2->next) {
		if (head1->next) {
			suma->exp = head1->exp;
			suma->koef = head1->koef;
			head1 = head1->next;
		}
		if (head2->next) {
			suma->exp = head2->exp;
			suma->koef = head2->koef;
			head2 = head2->next;
		}
		suma->next = (pozicija*)malloc(sizeof(pozicija));
		suma = suma->next;
		suma->next = NULL;
	}

	return 0;
}

int pomnozi(pozicija umnozak, pozicija head1, pozicija head2)
{
	pozicija i = NULL;
	pozicija j = NULL;

	for (i = head1->next; i != NULL; i = i->next)
	{
		for (j = head2->next; j != NULL; j = j->next)
		{
			pozicija noviElement = stvori(i->koef * j->koef, i->exp + j->exp);
			

			sortirano(umnozak, noviElement);
		}
	}
	return 0;
}









