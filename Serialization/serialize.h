#ifndef __SERIALIZE__
#define __SERIALIZE__

typedef struct serial_buffer {
#define SERIALIZE_BUFFER_DEFAULT_SIZE 1024
	void *b;
	int size;
	int next;
}ser_buff_t;



#endif
