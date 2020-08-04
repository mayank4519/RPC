#ifndef __SENTINAL__
#define __SENTINAL__

#include "serialize.h"

#define SENTINAL_INSERTION(b, obj) \
{ \
    if (!obj) { \
	unsigned int sentinal = 0XFFFFFFFF; \
        serialize_data(b, (char*)&sentinal, sizeof(unsigned int)); \
	return; \
    } \
}

#define SENTINAL_DETECTION(b) \
{ \
    unsigned int sentinal; \
    de_serialize_data((char*)&sentinal, b, sizeof(unsigned int)); \
    if (sentinal == 0xFFFFFFFF)	return NULL; \
    serialize_buffer_skip(b, -1 * sizeof(unsigned int)); \
}
#endif
