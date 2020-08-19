#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "person.h"

#define PORT 2000

int main() {

   ser_buff_t *buf;
   struct sockaddr_in addr, client_addr;
   int addrlen = sizeof(struct sockaddr);
   int sock, opt = 1, len = 0;

   /*Socker creation code start*/
   if((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
       perror("socket creation failed");
       exit(EXIT_FAILURE);
   }

   if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
			   &opt, sizeof(opt))) {
       perror("set socket option failed");
       exit(EXIT_FAILURE);
   }

   addr.sin_family = AF_INET;
   addr.sin_port = htons(PORT);
   addr.sin_addr.s_addr = INADDR_ANY;

   if(bind(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr)) == -1) {
       perror("socket bind failed");
       exit(EXIT_FAILURE);
   }
   /*Socker creation code end*/

   init_serialize_buffer(&buf);

   if ((len = recvfrom(sock, buf->b, buf->size, 0,
		   (struct sockaddr*)&client_addr, &addrlen)) == -1) {
      printf("Null bytes are recieved\n");
      return -1;
   }
   if (!buf || !(buf->b)) {
      printf("Received data is empty!!");
      free_serialize_buffer(buf);
      return -1;
   }

   printf("%d bytes of serialized data recieved on UNIX socket on port=%d \nbuf->size=%d buf->next=%d\n", len, PORT, buf->size, buf->next);
   
   person_t *p = deserialize_person(buf);
   if(!p)  {
       free_serialize_buffer(buf);
       return -1;
   }

   print_person(p);
   free_serialize_buffer(buf);
   free(p);
   close(sock);
}
