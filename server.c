#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "person.h"

#define PORT 8080

int main() {

   ser_buff_t *buf;
   struct sockaddr_in addr;
   int addrlen = sizeof(addr);
   int sock, new_sock, opt = 1;

   /*Socker creation code start*/
   if((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
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

   if(bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
       perror("socket bind failed");
       exit(EXIT_FAILURE);
   }

   if(listen(sock, 3) < 0) {
       perror("socket listen failed");
       exit(EXIT_FAILURE);
   }

   if(new_sock = accept(sock, (struct sockaddr*)&addr,
			   (socklen_t*)&addrlen) < 0) {
       perror("socket accept failed");
       exit(EXIT_FAILURE);
   }
   /*Socker creation code end*/

   init_serialize_buffer(&buf);

   read(new_sock, (ser_buff_t*)buf, 1024);
   printf("Serialized data recieved on UNIX socket on \nport=%d buf->size=%d buf->next=%d\n", PORT, buf->size, buf->next);

   if (!buf) {
      printf("Received data is empty!!");
      free_serialize_buffer(buf);
      return -1;
   }
   person_t *p = deserialize_person(buf);
   if(!p)  {
       free_serialize_buffer(buf);
       return -1;
   }
   print_person(p);
   
   //free_serialize_buffer(buf);
   //free(p);
}
