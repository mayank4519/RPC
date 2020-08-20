#ifndef __RPC_COMMON__
#define __RPC_COMMON__

#define PORT 2000
#define IP "127.0.0.1"

typedef struct rpc_hdr_s{
    uint8_t rpc_id;
    uint8_t payload_size;
}rpc_hdr_t;

#define SERIALIZED_HDR_SIZE sizeof(rpc_hdr_t)

#endif
