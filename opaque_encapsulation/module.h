





typedef struct Person_t Person_t;


Person_t* Person_init(char* first_name, char* surname, int age);

void Person_destroy(Person_t** pers);

void Person_print(Person_t* pers);
