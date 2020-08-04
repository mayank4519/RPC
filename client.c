#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "person.h"

#define PORT 8080

int main() {
   ser_buff_t *buf;
   int sock;
   person_t p;
   struct sockaddr_in addr;

   init_serialize_buffer(&buf);
   fill_person(&p);

   serialize_person(buf, &p);

   reset_serialize_buffer(buf);

   /*Socket creation start*/
   if((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
       perror("socket creation failed");
       exit(EXIT_FAILURE);
   }

   addr.sin_family = AF_INET;
   addr.sin_port = htons(PORT);

   if (inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr) <= 0) {
       perror("INvalid IP");
       exit(EXIT_FAILURE);
   }

   if(connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
       perror("socket connect failed");
       exit(EXIT_FAILURE);
   }

   send(sock, buf, 1024,0);
   printf("Serialized data sent over AF UNIX socket on port=%d", PORT);
   /*Socket creation end*/
   
   free_serialize_buffer(buf);
   free_person(&p);
}
