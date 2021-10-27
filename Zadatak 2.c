#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRMAX 1024

typedef struct _person {
    char name[STRMAX];
    char surname[STRMAX];
    int birthYear;
    struct _person* next;
} Person;

int prependList(Person* HEAD, Person* element);
int insertLast(Person* HEAD, Person* element);
int print(Person* HEAD);
Person* findElement(Person* HEAD, char* prezime);
int removeElement(Person* HEAD, Person* element);
Person* findLastElement(Person* HEAD);
Person* findPrevoius(Person* HEAD, Person* element);


int main(void)
{
    Person* HEAD;
    int status = 0;
    HEAD = (Person*)malloc(sizeof(Person));
    if (!HEAD)
        return -1;
    HEAD->next = NULL;

    return 0;
}

int prependList(Person* HEAD, Person* element)
{

    element->next = HEAD->next;
    HEAD->next = element;

    return 0;
}

int print(Person* HEAD)
{
    Person* P = HEAD->next;

    while (P != NULL) {
        printf("Ime: %s\nPrezime: %s\nGodina rodenja: %d\n\n", P->name, P->surname, P->birthYear);
        P = P->next;
    }

    return 0;
}

int insertLast(Person* HEAD, Person* element)
{
    Person* P = findLastElement(HEAD);

    element->next = NULL;
    P->next = element;

    return 0;
}

Person* findElement(Person* HEAD, char* prezime)
{
    Person* P = HEAD->next;

    while (P != NULL && strcmp(P->surname, prezime)) {
        P = P->next;
    }

    return P;
}

int removeElement(Person* HEAD, Person* element)
{
    Person* P = HEAD;

    while (P != NULL && P->next != element) {
        P = P->next;
    }

    if (P == NULL)
        return -1;
    else
    {
        P->next = P->next->next;
        free(element);
    }

    return 0;
}


Person* findLastElement(Person* HEAD)
{
    return findPrevoius(HEAD, NULL);
}

Person* findPrevoius(Person* HEAD, Person* element)
{
    Person* P = HEAD;

    while (P != NULL && P->next != element)
        P = P->next;

    return P;
}
