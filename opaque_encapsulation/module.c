#include "module.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


struct Person_t
{
    char first_name[100];
    char surname[100];
    int age;
};



Person_t* Person_init(char* first_name, char* surname, int age)
{
    Person_t* pers = (Person_t*)malloc(sizeof (Person_t));

    strcpy(pers->first_name, first_name);
    strcpy(pers->surname, surname);
    pers->age = age;

    return pers;
}


void Person_destroy(Person_t** pers)
{
    free(*pers);
    *pers = NULL;

}

void Person_print(Person_t* pers)
{
    if (!pers)
    {
        printf("Person does not exist\n");
        return;
    }

    printf("First name: %s\n", pers->first_name);
    printf("Surname: %s\n", pers->surname);
    printf("Age: %d\n", pers->age);
}