#ifndef __SERIALIZE__
#define __SERIALIZE__

typedef struct serial_buffer {
#define SERIALIZE_BUFFER_DEFAULT_SIZE 1024
	void *b;
	int size;
	int next;
}ser_buff_t;


void init_serialize_buffer(ser_buff_t **b);
void serialize_data(ser_buff_t *b, char *data, int nbytes);
void de_serialize_data(char *dest, ser_buff_t *b, int size);
void serialize_buffer_skip(ser_buff_t *b, int nbytes);
void free_serialize_buffer(ser_buff_t *b);
void reset_serialize_buffer(ser_buff_t *b);
#endif
