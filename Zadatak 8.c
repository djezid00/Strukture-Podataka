#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX (10)

typedef struct stablo* Stablo;
typedef struct stablo {
	int el;
	Stablo lijevo;
	Stablo desno;
};

Stablo unos(Stablo);
Stablo noviEl(Stablo, int);
int broj();
int Izbornik();
int inorder(Stablo);
int preorder(Stablo);
int postorder(Stablo);
Stablo findElement(Stablo, int);
Stablo findMinElement(Stablo);
Stablo izbrisiElement(const Stablo, Stablo);


int main()
{
	Stablo root;
	root = NULL;

	Izbornik();

	do
	{
		root = unos(root);
	} while (root);

	return 0;
}



Stablo noviEl(Stablo root,int Broj)
{
	Stablo novi = (Stablo)malloc(sizeof(Stablo));	
	novi = root;
	if (novi == NULL) {
		Stablo novi = (Stablo)malloc(sizeof(Stablo));
		novi->el = Broj;
		novi->lijevo = NULL;
		novi->desno = NULL;

		return novi;
	}

	else if (Broj > novi->el)
		novi->desno = noviEl(novi->desno, Broj);

	else if (Broj < novi->el)
		novi->lijevo = noviEl(novi->lijevo, Broj);

	return novi;
}

Stablo unos(Stablo root)
{
	int odabir = 0;
	Stablo izbor = NULL;

	printf("\nUnos: ");
	scanf("%d", &odabir);

	switch (odabir) {
	case 1:
		root = noviEl(root, broj());
		return root;
	case 2:
		printf("\nINORDER:");
		inorder(root);
		printf("\n");
		return root;
	
	case 3:
		printf("\nPREORDER:");
		preorder(root);
		printf("\n");
		return root;
	
	case 4:
		printf("\nPOSTORDER:");
		postorder(root);
		printf("\n");
		return root;
	case 5:	
		izbor = findElement(root, broj());
		izbrisiElement(root, izbor);
		return root;
	

	default:
		printf("Pogresan unos!\n");
		return 1;
	}

}

int broj()
{
	int br = 0;
	printf("Unesi broj: ");
	scanf("%d", &br);

	return br;
}


int preorder(Stablo root)
{
	if (root == NULL)
		return NULL;

	printf(" %d ", root->el);
	preorder(root->lijevo);
	preorder(root->desno);

	return EXIT_SUCCESS;
}

int inorder(Stablo root)
{
	if (root == NULL)
		return NULL;
	inorder(root->lijevo);
	printf(" %d ", root->el);
	inorder(root->desno);

	return EXIT_SUCCESS;
}
int postorder(Stablo root)
{
	if (root == NULL)
		return NULL;
	postorder(root->lijevo);
	postorder(root->desno);
	printf(" %d ", root->el);

	return EXIT_SUCCESS;	
}

Stablo findElement(Stablo root, int p)
{
	Stablo element = NULL;
	element = root;

	if (element == NULL)
		return NULL;

	else if (element->el == p)
		return element;

	else if (p > element->el)
		return findElement(element->desno, p);

	else if (p < element->el)
		return findElement(element->lijevo, p);

	return element;
}

Stablo findMinElement(Stablo root)
{
	if (root == NULL)
		return NULL;
	else if (root->lijevo == NULL)
		return root;

	return findMinElement(root->lijevo);
}

Stablo izbrisiElement(const Stablo root, Stablo obrisi)
{
	Stablo pom = (Stablo)root;
	Stablo temp = NULL;

	if (pom == NULL)
		return NULL;

	else if (obrisi->el < pom->el)
		pom->lijevo = izbrisiElement(pom->lijevo, obrisi);

	else if (obrisi->el > pom->el)
		pom->desno = izbrisiElement(pom->desno, obrisi);

	else if (pom->lijevo && pom->desno)
	{
		temp = findMinElement(pom->desno);
		pom->el = temp->el;
		pom->desno = izbrisiElement(pom->desno, pom);
	}

	else {
		temp = pom;

		if (pom->lijevo == NULL)
			pom = pom->desno;
		else
			pom = pom->lijevo;

		free(temp);
	}

	return pom;

}

int Izbornik()
{
	printf("-------------------------------------------------\n");
	printf("1 - Unesi novi element\n");
	printf("2 - INORDER\n");
	printf("3 - PREORDER\n");
	printf("4 - POSTORDER\n");
	printf("5 - Izbrisi element stabla\n");

	return 0;
}
