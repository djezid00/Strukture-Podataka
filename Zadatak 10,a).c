#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (128)

struct _grad;
typedef struct _grad* Stablo;
typedef struct _grad {
    char imeGrada[MAX_SIZE];
    int broj;
    Stablo L;
    Stablo D;
}grad;

struct _drzava;
typedef struct _drzava* Pozicija;
typedef struct _drzava {
    char imeDrzave[MAX_SIZE];
    Stablo root;
    Pozicija next;
}drzava;

int DatotekaDrzave(Pozicija head, char* fileName);
int SortUnos(Pozicija head, char* imeD, char* fileName);
Pozicija MakeEl(Pozicija head, char* imeD);
int Insert(Pozicija el, Pozicija new);
int DatotekaGradovi(Pozicija el, char* fileName);
Stablo Tree(Stablo root, char* imeG, int broj);
Stablo MakeTree(char* imeG, int broj);
int IspisDrzava(Pozicija head);
int IspisGrad(Stablo root);
int PretragaDrzava(Pozicija head);
int PretragaGradova(Stablo root, int broj, int* i);
int FreeAll(Pozicija head);
int FreeTree(Stablo root);
int Pop(Pozicija head);

int main()
{
    drzava head = { .imeDrzave = {0}, .root = NULL, .next = NULL };

    DatotekaDrzave(&head, "drzave.txt");

    IspisDrzava(&head);

    PretragaDrzava(&head);

    FreeAll(&head);

    return EXIT_SUCCESS;
}

int DatotekaDrzave(Pozicija head, char* fileName)
{
    FILE* fp = fopen(fileName, "r");
    char buffer[MAX_SIZE] = { 0 };
    char imeDrzave[MAX_SIZE] = { 0 };
    char datotekaGrad[MAX_SIZE] = { 0 };

    if (!fp)
    {
        printf("Datoteka nije otvorena!\n");
        return -1;
    }

    while (!feof(fp))
    {
        fgets(buffer, 1024, fp);

        if (sscanf(buffer, " %s %s", imeDrzave, datotekaGrad) == 2)
            SortUnos(head, imeDrzave, datotekaGrad);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

int SortUnos(Pozicija head, char* imeDrzave, char* fileName)
{
    Pozicija tempPrev = head;
    Pozicija tempNext = head->next;
    Pozicija element = NULL;

    while (tempNext)
    {
        if (strcmp(tempNext->imeDrzave, imeDrzave) > 0)
        {
            element = MakeEl(tempPrev, imeDrzave);
            DatotekaGradovi(element, fileName);
            return EXIT_SUCCESS;
        }

        tempPrev = tempPrev->next;
        tempNext = tempNext->next;
    }

    element = MakeEl(tempPrev, imeDrzave);
    DatotekaGradovi(element, fileName);

    return EXIT_SUCCESS;
}

Pozicija MakeEl(Pozicija el, char* imeDrzave)
{
    Pozicija novi = NULL;

    novi = (Pozicija)malloc(sizeof(drzava));
    if (!novi)
    {
        perror("Greska alociranja!\n");
        return NULL;
    }

    strcpy(novi->imeDrzave, imeDrzave);
    novi->root = NULL;
    novi->next = NULL;

    Insert(el, novi);

    return novi;
}

int Insert(Pozicija el, Pozicija novi)
{
    novi->next = el->next;
    el->next = novi;

    return EXIT_SUCCESS;
}

int DatotekaGradovi(Pozicija el, char* fileName)
{
    FILE* fp = fopen(fileName, "r");
    char buffer[MAX_SIZE] = { 0 };
    char imeGrada[MAX_SIZE] = { 0 };
    int broj = 0;

    if (!fp)
    {
        printf("Datoteka nije otvorena!\n");
        return -1;
    }

    while (!feof(fp))
    {
        fgets(buffer, 1024, fp);

        if (sscanf(buffer, " %s %d", imeGrada, &broj) == 2)
            el->root = Tree(el->root, imeGrada, broj);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

Stablo Tree(Stablo root, char* imeG, int broj)
{
    Stablo temp = NULL;

    if (!root)
        root = MakeTree(imeG, broj);

    else if (broj < root->broj)
        root->L = Tree(root->L, imeG, broj);

    else if (broj > root->broj)
        root->D = Tree(root->D, imeG, broj);

    else
    {
        if (strcmp(root->imeGrada, imeG) < 0)
        {
            if (root->D->broj == broj)
                root->D = Tree(root->D, imeG, broj);

            else
            {
                temp = root->D;
                root->D = MakeTree(imeG, broj);
                root->D->D = temp;
            }
        }

        else
        {
            if (root->L->broj == broj)
                root->L = Tree(root->L, imeG, broj);

            else
            {
                temp = root->L;
                root->L = MakeTree(imeG, broj);
                root->L->L = temp;
            }
        }
    }

    return root;
}

Stablo MakeTree(char* imeGrada, int broj)
{
    Stablo novi = NULL;
    novi = (Stablo)malloc(sizeof(grad));
    if (!novi)
    {
        perror("Greska alociranja!\n");
        return NULL;
    }

    strcpy(novi->imeGrada, imeGrada);
    novi->broj = broj;
    novi->L = NULL;
    novi->D = NULL;

    return novi;
}

int IspisDrzava(Pozicija head)
{
    while (head->next)
    {
        printf("%s\n", head->next->imeDrzave);
        IspisGrad(head->next->root);
        head = head->next;
    }

    return EXIT_SUCCESS;
}

int IspisGrad(Stablo root)
{
    if (root->L)
        IspisGrad(root->L);

    printf("    %s\n", root->imeGrada);

    if (root->D)
        IspisGrad(root->D);

    return EXIT_SUCCESS;
}

int PretragaDrzava(Pozicija head)
{
    char ime[MAX_SIZE] = { 0 };
    int broj = 0, i = 0;
    Pozicija temp = NULL;

    printf("Koju drzavu zelite pretraziti?\n");
    scanf(" %s", ime);
    while (head->next)
    {
        if (!strcmp(head->next->imeDrzave, ime))
        {
            temp = head->next;
            break;
        }
        head = head->next;
    }
    if (!head->next)
    {
        printf("Drzava ne postoji!\n");
        return -1;
    }

    printf("Upisite broj stanovnika za usporedbu:\n");
    scanf(" %d", &broj);
    PretragaGradova(temp->root, broj, &i);

    if (!i)
        printf("Nepostojeci gradovi!\n");

    return EXIT_SUCCESS;
}

int PretragaGradova(Stablo root, int broj, int* i)
{
    if (root->broj > broj)
    {
        printf("%s\n", root->imeGrada);
        (*i)++;
        if (root->L)
            if (root->L->broj > broj)
                PretragaGradova(root->L, broj, i);
    }

    if (!root->D)
        return EXIT_SUCCESS;

    if (root->D->broj > broj)
        PretragaGradova(root->D, broj, i);

    return EXIT_SUCCESS;
}

int FreeAll(Pozicija head)
{
    while (head->next)
    {
        FreeTree(head->next->root);
        Pop(head);
    }

    return EXIT_SUCCESS;
}

int FreeTree(Stablo root)
{
    if (!root)
        return EXIT_SUCCESS;

    FreeTree(root->L);

    FreeTree(root->D);

    free(root);

    return EXIT_SUCCESS;
}

int Pop(Pozicija head)
{
    Pozicija temp = head->next;

    head->next = temp->next;
    free(temp);

    return EXIT_SUCCESS;
}