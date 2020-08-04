#ifndef __PERSON__
#define __PERSON__

#include "serialize.h"

#define MAX_NAME_SIZE 30

typedef struct occupation_s occupation_t;

typedef struct person_s {
    char name[MAX_NAME_SIZE];
    int age;
    int weight;
    occupation_t *occ;
}person_t;

struct occupation_s {
    char dep_name[MAX_NAME_SIZE];
    int emp_id;
};

void fill_person(person_t *p);
void free_person(person_t *p);
void print_person(person_t *p);
void serialize_person(ser_buff_t *buf, person_t *p);
person_t* deserialize_person(ser_buff_t *b);
#endif
