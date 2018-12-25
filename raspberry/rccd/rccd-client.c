#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 31415       
#define BUFFER_SIZE 1024

int main(void) {
    int sockfd, len;
    int res;

     struct sockaddr_in srvr_addr; // server address information
     FILE *fd=fopen("test-client.jpg","wb");	
     char buf_out[]= "raspistill -o /tmp/clent.jpg";
     char *buf_in;

     buf_in = (char *)malloc(BUFFER_SIZE*sizeof(char)); 

     if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      perror("socket");
      exit(1);
    }
    srvr_addr.sin_family = AF_INET;      // host byte order
    srvr_addr.sin_port = htons(PORT); // short, network byte order
    srvr_addr.sin_addr.s_addr = inet_addr("192.168.1.201");
    memset(&(srvr_addr.sin_zero),'\0', 8); // zero the rest of the struct
    if (connect(sockfd, (struct sockaddr *)&srvr_addr,
    sizeof(struct sockaddr)) == -1) {
      perror("connect");
      exit(1);
    }
    
    printf("Conectado al socket\n");
    send(sockfd, buf_out, 1024*sizeof(char),0);
    printf("Enviado al socket: %s\n", buf_out);

    memset(buf_in, '\0', BUFFER_SIZE*sizeof(char));

  /* send info to client */
    while ( (res = recv(sockfd, buf_in, BUFFER_SIZE*sizeof(char),0)) > 0 ) { /* begin - while */
      res = fwrite(buf_in, sizeof(char), res, fd);
      memset(buf_in, '\0', BUFFER_SIZE*sizeof(char)); /* buffer cleaning */
      fflush(fd);
  } /* end - while */
    fclose(fd);	    	
    close(sockfd);

    return 0;
}

