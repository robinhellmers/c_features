#include <stdio.h>
#include "module.h"
#include <stdio.h>




int main(void)
{   
    Person_t* pers_one = NULL;
    Person_t* pers_two = NULL;

    pers_one = Person_init("Robin", "Hellmers", 24);
    pers_two = Person_init("Kajsa", "Eliasson", 21);

    printf("Person 1:\n");
    Person_print(pers_one);
    printf("\n");
    printf("Person 2:");
    Person_print(pers_two);
    printf("\n");

    Person_destroy(&pers_one);
    Person_destroy(&pers_two);

    printf("Person 1:\n");
    Person_print(pers_one);
    printf("\n");
    printf("Person 2:\n");
    Person_print(pers_two);
    printf("\n");

    

    return 0;
}