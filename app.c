#include <stdio.h>
#include <stdlib.h>
#include "person.h"

int main() {
   ser_buff_t *buf;
   person_t p;

   init_serialize_buffer(&buf);
   fill_person(&p);

   serialize_person(buf, &p);

   reset_serialize_buffer(buf);

   person_t *p2 = deserialize_person(buf);
   if(p2) print_person(p2);
   
   free_serialize_buffer(buf);
   free_person(&p);
   free(p2);
}
