#include "person.h"
#include "sentinal.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>

void
fill_person(person_t *p) {

    strncpy((p)->name, "Mayank", strlen("Mayank"));
    p->name[strlen("Mayank")] = '\0';
    (p)->age = 26;
    (p)->weight = 70;

    (p)->occ = (occupation_t*)calloc(1, sizeof(occupation_t));
    strncpy((p)->occ->dep_name, "RD", strlen("RD"));
    p->occ->dep_name[strlen("RD")] = '\0';
    (p)->occ->emp_id = 100;
}

void
print_person(person_t *p) {

    printf("Person details.\n");
    printf("Name=%s\n", p->name);
    printf("Age=%d\n", p->age);
    printf("Weight=%d\n", p->weight);

    printf("Occupation details\n");
    printf("Dept. name=%s\n", p->occ->dep_name);
    printf("EMP ID=%d\n", p->occ->emp_id);
}

void
free_person(person_t *p) {

    free(p->occ);
}

void
serialize_occupation(ser_buff_t *b, occupation_t *occ) {

   SENTINAL_INSERTION(b, occ);

   serialize_data(b, (char*)occ->dep_name, MAX_NAME_SIZE); 
   serialize_data(b, (char*)&(occ->emp_id), sizeof(int)); 

}

void
serialize_person(ser_buff_t *b, person_t *p) {

   SENTINAL_INSERTION(b, p);
  
   serialize_data(b, (char*)p->name, MAX_NAME_SIZE); 
   serialize_data(b, (char*)&(p->age), sizeof(int)); 
   serialize_data(b, (char*)&(p->weight), sizeof(int));
   serialize_occupation(b, p->occ);
}

occupation_t*
deserialize_occupation(ser_buff_t *b) {

    SENTINAL_DETECTION(b);

    occupation_t *occ = (occupation_t*)calloc(1, sizeof(occupation_t));
    
    de_serialize_data((char*)occ->dep_name, b, MAX_NAME_SIZE);
    de_serialize_data((char*)&(occ->emp_id), b, sizeof(int));
    return occ;
}

person_t*
deserialize_person(ser_buff_t *b) {

    SENTINAL_DETECTION(b);

    person_t *p = (person_t*)calloc(1, sizeof(person_t));

    de_serialize_data((char*)p->name, b, MAX_NAME_SIZE);
    de_serialize_data((char*)&(p->age), b, sizeof(int));
    de_serialize_data((char*)&(p->weight), b, sizeof(int));

    p->occ = deserialize_occupation(b);
    return p;
}
