#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _stablo;
typedef struct _stablo* Stablo;
typedef struct _stablo {
	int el;
	Stablo L;
	Stablo D;
}Tree;

int Izbornik();
Stablo Izbor(Stablo root);
int broj();
Stablo noviEl(Stablo root,int broj);
int Inorder(Stablo root);
int Preorder(Stablo root);
int Postorder(Stablo root);
int LevelOrder(Stablo root);
int Height(Stablo root);
int PrintLevel(Stablo root, int level);
Stablo findElement(Stablo root, int broj);
Stablo DeleteNode(Stablo root,Stablo izbor);
Stablo FindMin(Stablo root);
Stablo DealocirajStablo(Stablo root);



int main()
{
	Stablo root = NULL;

	Izbornik();

	do
	{
		root = Izbor(root);
	} while (root);



	return EXIT_SUCCESS;
}

int Izbornik()
{
	printf("0.PREKID\n");
	printf("1.UNOS NOVOG ELEMENTA:\n");
	printf("2.PREORDER:\n");
	printf("3.INORDER:\n");
	printf("4.POSTORDER:\n");
	printf("5.LEVELORDER:\n");
	printf("6.TRAZI ELEMENT:\n");
	printf("7.IZBRISI ELEMENT:\n");


	return EXIT_SUCCESS;
}

Stablo Izbor(Stablo root)
{
	Stablo izbor = NULL;
	int odabir=0;

	printf("\nUnos:");
	scanf(" %d",&odabir);

	
		switch (odabir)
		{
		case 0:
			DealocirajStablo(root);
			printf("\nUspjesna dealokacija!\n");
			return NULL;

		case 1:
			root = noviEl(root, broj());
			return root;
		case 2:
			Preorder(root);
			return root;

		case 3:
			Inorder(root);
			return root;

		case 4:
			Postorder(root);
			return root;

		case 5:
			LevelOrder(root);
			return root;
		
		case 6:
			izbor = findElement(root, broj());
			printf("\nELEMENT=%d\n",izbor->el);
			return root;

		case 7:
			izbor = findElement(root, broj());
			DeleteNode(root, izbor);
			return root;

		default:
			return NULL;
		}
}

int broj()
{
	int broj = 0;
	printf("Unesite broj:");
	scanf(" %d",&broj);

	return broj;
}

Stablo noviEl(Stablo root, int broj)
{
	Stablo novi = NULL;
	
	novi = root;

	if (novi == NULL)
	{
		novi = (Stablo)malloc(sizeof(Tree));
		if (!novi)
		{
			printf("Greska alokacije!\n");
			return -1;
		}
		novi->el = broj;
		novi->L = NULL;
		novi->D = NULL;
	}

	else if (broj < novi->el)
		novi->L = noviEl(novi->L, broj);
	else if (broj > novi->el)
		novi->D = noviEl(novi->D,broj);

	return novi;
}


int Inorder(Stablo root)
{
	if (root == NULL)
		return NULL;
	Inorder(root->L);
	printf("%d ",root->el);
	Inorder(root->D);

	return EXIT_SUCCESS;
}

int Preorder(Stablo root)
{
	if (root == NULL)
		return NULL;
	printf("%d ",root->el);
	Preorder(root->L);
	Preorder(root->D);

	return EXIT_SUCCESS;
}

int Postorder(Stablo root)
{
	if (root == NULL)
		return NULL;
	
	Postorder(root->L);
	Postorder(root->D);
	printf("%d ", root->el);

	return EXIT_SUCCESS;
}

int LevelOrder(Stablo root)
{
	int h = Height(root);
	int i = 0;

	for (i = 1; i <= h; i++)
	{
		PrintLevel(root,i);
	}

	return EXIT_SUCCESS;
}

int Height(Stablo root)
{
	int lheight = 0;
	int rheight = 0;
	if (root == NULL)
		return NULL;
	else
	{
		lheight = Height(root->L);
		rheight = Height(root->D);

		if (lheight > rheight)
			return(lheight + 1);
		else 
			return (rheight + 1);
	}

}

int PrintLevel(Stablo root, int level)
{
	if (root == NULL)
		return NULL;

	if (level == 1)
		printf("%d ",root->el);

	else if (level > 1)
	{
		PrintLevel(root->L,level -1);
		PrintLevel(root->D,level-1);

	}

	return EXIT_SUCCESS;
}

Stablo findElement(Stablo root, int broj)
{
	if (root == NULL)
		return NULL;
	if (broj < root->el)
		return findElement(root->L, broj);
	else if (broj > root->el)
		return findElement(root->D,broj);


	return root;

}

Stablo DeleteNode(Stablo root, Stablo izbor)
{
	Stablo temp = NULL;
	if (root == NULL)
		return NULL;

	else if (izbor->el < root->el)
		root->L = DeleteNode(root->L,izbor);
	else if (izbor->el > root->el)
		root->D = DeleteNode(root->D, izbor);
	else
	{
		//1) nema djece
		if (root->L == NULL && root->D == NULL)
		{
			free(root);
			root = NULL;
		}
		//2) jedno dijete
		else if (root->L == NULL) {
			temp = root;
			root = root->D;
			free(temp);
		}
		else if (root->D == NULL)
		{
			temp = root;
			root = root->L;
			free(temp);
		}
		//3)dvoje djece
		else
		{
			temp = FindMin(root->D);
			root->el = temp->el;
			root->D = DeleteNode(root->D,temp->el);

		}
			
	}

	return root;
}

Stablo FindMin(Stablo root)
{
	while (root->L != NULL)
		root = root->L;

	return root;
}

Stablo DealocirajStablo(Stablo root)
{
	if (root != NULL)
	{
		DealocirajStablo(root->L);
		DealocirajStablo(root->D);
		free(root);
	}


	return NULL;
}

