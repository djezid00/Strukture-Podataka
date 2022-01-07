#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (128)

struct _grad;
typedef struct _grad* Pozicija;
typedef struct _grad {
    char imeGrada[MAX_SIZE];
    int broj;
    Pozicija next;
}grad;

struct _drzava;
typedef struct _drzava* Stablo;
typedef struct _drzava {
    char imeDrzave[MAX_SIZE];
    Stablo L;
    Stablo D;
    grad head;
}drzava;

Stablo DatotekaDrzave(Stablo root, char* fileName);
Stablo Tree(Stablo root, char* imeD, char* fileName);
Stablo StvoriStablo(char* imeD);
int DatotekaGradovi(Stablo el, char* fileName);
int SortUnos(Pozicija head, char* imeG, int broj);
int StvoriEl(Pozicija el, char* imeG, int broj);
int Insert(Pozicija el, Pozicija new);
int IspisDrzava(Stablo root);
int IspisGrad(Pozicija head);
int PretragaDrzava(Stablo root);
Stablo PretragaSabla(Stablo root, char* ime);
int PretragaGrada(Pozicija head, int broj, int* i);
int FreeAll(Stablo root);
int FreeList(Pozicija head);

int main()
{
    Stablo root = NULL;

    root = DatotekaDrzave(root, "drzave.txt");

    IspisDrzava(root);

    PretragaDrzava(root);

    FreeAll(root);

    return EXIT_SUCCESS;
}

Stablo DatotekaDrzave(Stablo root, char* fileName)
{
    FILE* fp = fopen(fileName, "r");
    char buffer[MAX_SIZE] = { 0 };
    char imeDrzave[MAX_SIZE] = { 0 };
    char datotekaGrad[MAX_SIZE] = { 0 };

    if (!fp)
    {
        printf("Datoteka nije otvorena!\n");
        return NULL;
    }

    while (!feof(fp))
    {
        fgets(buffer, 1024, fp);

        if (sscanf(buffer, " %s %s", imeDrzave, datotekaGrad) == 2)
            root = Tree(root, imeDrzave, datotekaGrad);
    }

    fclose(fp);

    return root;
}

Stablo Tree(Stablo root, char* imeDrzave, char* fileName)
{
    if (!root)
    {
        root = StvoriStablo(imeDrzave);
        DatotekaGradovi(root, fileName);
    }

    else if (strcmp(root->imeDrzave, imeDrzave) > 0)
        root->L = Tree(root->L, imeDrzave, fileName);

    else
        root->D = Tree(root->D, imeDrzave, fileName);

    return root;
}

Stablo StvoriStablo(char* imeDrzave)
{
    Stablo novi = NULL;
    novi = (Stablo)malloc(sizeof(drzava));
    if (!novi)
    {
        perror("Greska alociranja!\n");
        return NULL;
    }

    strcpy(novi->imeDrzave, imeDrzave);
    strcpy(novi->head.imeGrada, "");
    novi->head.broj = 0;
    novi->head.next = NULL;
    novi->L = NULL;
    novi->D = NULL;

    return novi;
}

int DatotekaGradovi(Stablo el, char* fileName)
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
            SortUnos(&el->head, imeGrada, broj);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

int SortUnos(Pozicija head, char* imeG, int broj)
{
    Pozicija tempPrev = head;
    Pozicija tempNext = head->next;

    while (tempNext)
    {
        if (tempNext->broj > broj)
        {
            StvoriEl(tempPrev, imeG, broj);
            return EXIT_SUCCESS;
        }

        else if (tempNext->broj == broj)
            if (strcmp(tempNext->imeGrada, imeG) > 0)
            {
                StvoriEl(tempPrev, imeG, broj);
                return EXIT_SUCCESS;
            }

        tempPrev = tempPrev->next;
        tempNext = tempNext->next;
    }

    StvoriEl(tempPrev, imeG, broj);

    return EXIT_SUCCESS;
}

int StvoriEl(Pozicija el, char* imeGrada, int broj)
{
    Pozicija new = NULL;

    new = (Pozicija)malloc(sizeof(grad));
    if (!new)
    {
        perror("Greska alociranja!\n");
        return -1;
    }

    strcpy(new->imeGrada, imeGrada);
    new->broj = broj;
    new->next = NULL;

    Insert(el, new);

    return EXIT_SUCCESS;
}

int Insert(Pozicija el, Pozicija new)
{
    new->next = el->next;
    el->next = new;

    return EXIT_SUCCESS;
}

int IspisDrzava(Stablo root)
{
    if (root->L)
        IspisDrzava(root->L);

    printf("%s\n", root->imeDrzave);
    IspisGrad(&root->head);

    if (root->D)
        IspisDrzava(root->D);

    return EXIT_SUCCESS;
}

int IspisGrad(Pozicija head)
{
    while (head->next)
    {
        printf("    %s\n", head->next->imeGrada);
        head = head->next;
    }

    return EXIT_SUCCESS;
}

int PretragaDrzava(Stablo root)
{
    char ime[MAX_SIZE] = { 0 };
    int broj = 0, i = 0;
    Stablo temp = NULL;

    printf("Koju drzavu zelite pretraziti?\n");
    scanf(" %s", ime);
    temp = PretragaSabla(root, ime);
    if (!temp)
    {
        printf("Drzava ne postoji!\n");
        return -1;
    }

    printf("Upisite broj stanovnika za usporedbu:\n");
    scanf(" %d", &broj);
    PretragaGrada(&temp->head, broj, &i);

    return EXIT_SUCCESS;
}

Stablo PretragaSabla(Stablo root, char* ime)
{
    if (!strcmp(root->imeDrzave, ime))
        return root;

    else if (strcmp(root->imeDrzave, ime) > 0)
        PretragaSabla(root->D, ime);

    else
        PretragaSabla(root->L, ime);

    return NULL;
}

int PretragaGrada(Pozicija head, int broj, int* i)
{
    while (head->next)
    {
        if (head->next->broj > broj)
        {
            (*i)++;
            printf("%s\n", head->next->imeGrada);
        }
        head = head->next;
    }

    return EXIT_SUCCESS;
}

int FreeAll(Stablo root)
{
    if (!root)
        return EXIT_SUCCESS;

    FreeList(&root->head);

    FreeAll(root->L);

    FreeAll(root->D);

    free(root);

    return EXIT_SUCCESS;
}

int FreeList(Pozicija head)
{
    Pozicija temp = NULL;

    while (head->next)
    {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    return EXIT_SUCCESS;
}