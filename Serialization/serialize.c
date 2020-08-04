#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include "serialize.h"

void
init_serialize_buffer(ser_buff_t **b) {

    *b = (ser_buff_t*)calloc(1, sizeof(ser_buff_t));
    (*b)->b = calloc(1, SERIALIZE_BUFFER_DEFAULT_SIZE);
    (*b)->size = SERIALIZE_BUFFER_DEFAULT_SIZE;
    (*b)->next = 0;
}


void
init_serialize_buffer_defined_size(ser_buff_t **b, int size) {

    *b = (ser_buff_t*)calloc(1, sizeof(ser_buff_t));
    (*b)->b = calloc(1, size);
    (*b)->size = size;
    (*b)->next = 0;
}

char
is_serialize_buffer_empty(ser_buff_t *b) {

    if(0 == b->next)
	return 1;
    return 0;    
}

void
free_serialize_buffer(ser_buff_t *b) {

	free(b->b);
	free(b);
}

int
get_serialize_buffer_length(ser_buff_t *b) {

    return b->size;
}

char*
get_serialize_buffer_current_ptr_offset(ser_buff_t *b) {

    if(b == NULL)
	return NULL;
    return b->b + b->next;
}

int
get_serialize_buffer_available_size(ser_buff_t *b) {

    return b->size - b->next;
}

void
serialize_data(ser_buff_t *b, char *data, int nbytes) {

    int avail_size = get_serialize_buffer_available_size(b);
    int resize_flag = 0;

    //increase the total buffer size
    while (avail_size < nbytes) {
	b->size *= 2;
	avail_size = get_serialize_buffer_available_size(b);
	resize_flag = 1;
    }

    if (resize_flag == 0) {
        memcpy(b->b + b->next, data, nbytes);
    	b->next += nbytes;
    	return;
    }

    b->b = realloc(b->b, b->size);
    memcpy(b->b + b->next, data, nbytes);
    b->next += nbytes;
    return;
}

void
de_serialize_data(char *dest, ser_buff_t *b, int size) {

    if (b == NULL || (b->b == NULL)) assert(0);
    if((b->size - b->next) < size)  assert(0);
    if(!size)  return;

    memcpy(dest, b->b + b->next, size);
    b->next += size;
}

void
serialize_buffer_skip(ser_buff_t *b, int nbytes) {

    int avail_size = get_serialize_buffer_available_size(b);
    int resize_flag = 0;

    //increase the total buffer size
    while (avail_size < nbytes) {
        b->size *= 2;
        avail_size = get_serialize_buffer_available_size(b);
        resize_flag = 1;
    }
 
    if (resize_flag == 0) {
	b->next += nbytes;
	return;
    }

    b->b = realloc(b->b, b->size);
    b->next += nbytes;
}

void
reset_serialize_buffer(ser_buff_t *b) {

    b->next = 0;
}
