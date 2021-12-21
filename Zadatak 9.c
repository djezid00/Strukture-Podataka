#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MIN_ROUND (90)
#define MAX_ROUND (10)
#define MAX_SIZE (100)

typedef struct stablo* Stablo;
typedef struct stablo {
    int broj;
    Stablo desno;
    Stablo lijevo;
};

typedef struct cvor* Pozicija;
typedef struct cvor {
    int broj;
    Pozicija next;
};

Stablo Insert(Stablo root, int broj);
Stablo Add(int broj);
int InorderPrint(Stablo root);
int FreeAll(Stablo root);
int Replace(Stablo root);
int MakeList(Stablo root, Pozicija head);
int InsertList(Pozicija head, int broj);
Pozicija AddList(int broj);
int Datoteka(Pozicija head, char* ime);
int Pop(Pozicija head);

int main()
{
    Stablo root = NULL;
    Pozicija head = NULL;
    head = (Pozicija)malloc(sizeof(struct cvor));
    int i = 0;
    int niz[11] = { 2,5,7,8,11,1,4,2,3,7,0 };
    char ime[MAX_SIZE] = { 0 };

    srand((unsigned)time(NULL));

    while (niz[i])
    {
        root = Insert(root, niz[i]);
        i++;
    }

    InorderPrint(root);
    printf("\n");

    Replace(root);

    InorderPrint(root);
    printf("\n");

    FreeAll(root);
   
    root = NULL;
    printf("Koliko ce cvorova imati stablo?\n");
    scanf(" %d", &i);
    while (i)
    {
        root = Insert(root, rand() % (MIN_ROUND - MAX_ROUND - 1) + MAX_ROUND + 1);
        i--;
    }

    MakeList(root, &head);

    printf("Kako ce se zvati datoteka?\n");
    scanf(" %s", ime);
    Datoteka(&head, ime);

    Replace(root);
    MakeList(root, &head);
    Datoteka(&head, ime);

    FreeAll(root);

    return EXIT_SUCCESS;
}

Stablo Insert(Stablo root, int broj)
{
    if (!root)
        root = Add(broj);

    else if (broj >= root->broj)
        root->lijevo = Insert(root->lijevo, broj);

    else
        root->desno = Insert(root->desno, broj);

    return root;
}

Stablo Add(int broj)
{
    Stablo novi = NULL;
    novi = (Stablo)malloc(sizeof(struct stablo));
    if (!novi)
    {
        perror("Greska alociranja!\n");
        return NULL;
    }

    novi->broj = broj;
    novi->lijevo = NULL;
    novi->desno = NULL;

    return novi;
}

int InorderPrint(Stablo root)
{
    if (root->desno)
        InorderPrint(root->desno);

    printf("%d ", root->broj);

    if (root->lijevo)
        InorderPrint(root->lijevo);

    return EXIT_SUCCESS;
}

int FreeAll(Stablo root)
{
    if (!root)
        return EXIT_SUCCESS;

    FreeAll(root->lijevo);

    FreeAll(root->desno);

    free(root);

    return EXIT_SUCCESS;
}

int Replace(Stablo root)
{
    int desno = 0, lijevo = 0;

    if (root->desno)
        desno = root->desno->broj + Replace(root->desno);

    if (root->lijevo)
        lijevo = root->lijevo->broj + Replace(root->lijevo);

    root->broj = desno + lijevo;

    return root->broj;
}

int MakeList(Stablo root, Pozicija head)
{
    if (root->desno)
        MakeList(root->desno, head);

    InsertList(head, root->broj);

    if (root->lijevo)
        MakeList(root->lijevo, head);

    return EXIT_SUCCESS;
}

int InsertList(Pozicija head, int broj)
{
    Pozicija novi = NULL;

    novi = AddList(broj);

    while (head->next)
        head = head->next;

    head->next = novi;

    return EXIT_SUCCESS;
}

Pozicija AddList(int broj)
{
    Pozicija novi = NULL;
    novi = (Pozicija)malloc(sizeof(struct cvor));
    if (!novi)
    {
        perror("Greska alociranja!\n");
        return NULL;
    }

    novi->broj = broj;
    novi->next = NULL;

    return novi;
}

int Datoteka(Pozicija head, char* ime)
{
    FILE* fp = fopen(ime, "w");
    if (!fp)
    {
        printf("Nemoguce otvoriti datoteku!\n");
        return -1;
    }

    while (head->next)
    {
        fprintf(fp, "%d    ", head->next->broj);
        Pop(head);
    }

    fprintf(fp, "\n");

    fclose(fp);

    return EXIT_SUCCESS;
}

int Pop(Pozicija head)
{
    Pozicija temp = head->next;

    head->next = temp->next;
    free(temp);

    return EXIT_SUCCESS;
}