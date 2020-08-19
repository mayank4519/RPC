#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include "person.h"

#define PORT 2000

int main() {
   ser_buff_t *buf;
   int sock, addr_len;
   person_t p;
   struct sockaddr_in addr;
   addr_len = sizeof(struct sockaddr);

   init_serialize_buffer(&buf);
   fill_person(&p);

   serialize_person(buf, &p);

   reset_serialize_buffer(buf);

   /*Socket creation start*/
   if((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
       perror("socket creation failed");
       exit(EXIT_FAILURE);
   }

   addr.sin_family = AF_INET;
   addr.sin_port = htons(PORT);

   struct hostent *host = (struct hostent*)gethostbyname("127.0.0.1");
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
