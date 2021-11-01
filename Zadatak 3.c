#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE (100)

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    Position next;
}Person;


Position stvori(char* name, char* surname, int birthYear);
int sortiraj(Position head, Position newPerson);
int umetni_nakon(Position position, Position newPerson);
int dodaj(Position head, int position);
Position pronadji(Position first, int position);
int ucitaj_iz_file(Position head, char* fileName);
int upis_u_file(Position head, char* fileName);
int FreeAll(Position head);
int ispis(Position first);

int main()
{
    Person = { head.next = NULL, 
        head.name = {0}, 
        head.surname = {0},
        head.birthYear = 0 
    };
    char ime_dat[MAX_SIZE] = { 0 };
    int a = 0;

    printf("Naziv datoteke za citanje?\n");
    scanf(" %s", ime_dat);
    ucitaj_iz_file(&head, ime_dat);

    printf("Ispis nakon sortiranja:\n");
    ispis(head.next);

    printf("Nakon kojeg elementa zelite dodati element?\n");
    scanf(" %d", &a);
    dodaj(&head, a);

    printf("Prije kojeg elementa elite dodati element\n");
    scanf(" %d", &a);
    dodaj(&head, a - 1);

    printf("Naziv datoteke za upis podataka?\n");
    scanf(" %s", ime_dat);
    upis_u_file(&head, ime_dat);

    return EXIT_SUCCESS;
}


Position stvori(char* name, char* surname, int birthYear)
{
    Position osoba = NULL;

    osoba = (Position)malloc(sizeof(Person));
    if (!osoba)
    {
        printf("GRESKA ALOCIRANJA!\n");
        return NULL;
    }

    strcpy(osoba->name, name);
    strcpy(osoba->surname, surname);
    osoba->birthYear = birthYear;
    osoba->next = NULL;


    return osoba;
}

int ucitaj_iz_file(Position head, char* ime_dat)
{
    Position osoba = NULL;
    FILE* fp = fopen(ime_dat, "r");
    char buffer[MAX_SIZE] = { 0 };
    char name[MAX_SIZE] = { 0 };
    char surname[MAX_SIZE] = { 0 };
    int birthYear = 0;

    if (!fp)
    {
        printf("Datoteka ne postoji!\n");
        return -1;
    }

    while (!feof(fp))
    {
        fgets(buffer, 1024, fp);
        if (scanf(buffer, " %s %s %d", name, surname, &birthYear) == 3)
        {
            osoba = stvori(name, surname, birthYear);
            sortiraj(head, osoba);
        }
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

int umetni_nakon(Position position, Position osoba)
{
    osoba->next = position->next;
    position->next = osoba;

    return EXIT_SUCCESS;
}

int dodaj(Position head, int position)
{
    Position personBefore = NULL;
    Position osoba = NULL;
    char name[MAX_SIZE] = { 0 };
    char surname[MAX_SIZE] = { 0 };
    int birthYear = 0;

   

    personBefore = pronadji(head, position);


    scanf(" %s %s %d", name, surname, &birthYear);
    osoba = stvori(name, surname, birthYear);

    umetni_nakon(personBefore, osoba);

    return EXIT_SUCCESS;
}

Position pronadji(Position head, int position)
{
    Position temp = head;

    while (position)
    {
        temp = temp->next;
        if (!temp->next)
        {
            return NULL;
        }
        position--;
    }

    return temp;
}

int upis_u_file(Position head, char* ime_dat)
{
    Position temp = head;
    FILE* fp = fopen(ime_dat, "w");
    
    while (temp->next)
    {
        temp = temp->next;
        fprintf(fp, "%s\t %s\t %d\t\n", temp->name, temp->surname, temp->birthYear);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}

int ispis(Position first)
{
    Position temp = first;
    while (temp)
    {
        printf("Ime: %s\t, Prezime: %s\t, Godina: %d\t\n", temp->name, temp->surname, temp->birthYear);
        temp = temp->next;
    }

    return EXIT_SUCCESS;
}

