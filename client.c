#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include "person.h"
#include "rpc_common.h"

int main() {
   ser_buff_t *buf;
   int sock, addr_len;
   person_t p;
   rpc_hdr_t rpc_hdr;
   struct sockaddr_in addr;
   addr_len = sizeof(struct sockaddr);
 
   /*Intialize RPC data structure*/ 
   rpc_hdr.rpc_id = 1;
   rpc_hdr.payload_size = 0;

   /*Intialize serial buffer data structure*/ 
   init_serialize_buffer(&buf);

   /*Generate some data to serialize*/
   fill_person(&p);

   /*Skip 16 bytes for rpc header in the serial buffer*/
   serialize_buffer_skip(buf, SERIALIZED_HDR_SIZE); 

   /*Finally serialize the data*/
   serialize_person(buf, &p);

   /*FIll the rpc header after serialization*/
   rpc_hdr.payload_size = get_serialize_buffer_data_size(buf)
	  		   - SERIALIZED_HDR_SIZE;

   copy_in_serialized_buf_by_offset(buf, (char*)&rpc_hdr.rpc_id, 
		   sizeof(rpc_hdr.rpc_id), 0);
   copy_in_serialized_buf_by_offset(buf, (char*)&rpc_hdr.payload_size, 
		   sizeof(rpc_hdr.payload_size), sizeof(rpc_hdr.rpc_id));

   reset_serialize_buffer(buf);

   /*Socket creation start*/
   if((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
       perror("socket creation failed");
       exit(EXIT_FAILURE);
   }

   addr.sin_family = AF_INET;
   addr.sin_port = htons(PORT);

   struct hostent *host = (struct hostent*)gethostbyname(IP);
   addr.sin_addr = *((struct in_addr*)host->h_addr);
   /*Socket creation end*/

   int bytes = sendto(sock, buf->b, buf->size, 0,
		   (struct sockaddr*)&addr, sizeof(struct sockaddr));

   printf("%d bytes of serialized data sent over AF UNIX socket on port=%d", 
		   bytes, PORT);

   free_serialize_buffer(buf);
   free_person(&p);
   close(sock);
}
