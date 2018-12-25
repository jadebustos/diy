/* (c) 2013 jadebustos <jadebustos@gmail.com> */
/*     Distributed under GNU GPL v2 License                   */
/*     See COPYING.txt for more details                       */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <arpa/inet.h>

#include "log-service.h"
#include "rccd.h"

#define TRUE 1  

void rccd (rccd_conf *conf) { /* begin - rccd function */

  int socketfd, /* socket */
      i = 0;

  struct sockaddr_in server; /* server addr information */

  char cltadd[INET_ADDRSTRLEN],
       cmdcheck[] = "raspistill";

  int msgsock,
    msgsize,
    cmdstatus,
    cmdlength;

  char buf_in[conf->cmd_length], /* input buffer */
    *filename;

  socketfd = socket(AF_INET, SOCK_STREAM, 0); /* socket creation */

  if( socketfd < 0 ) {  /* begin - if */
    log_service(conf, "Error opening the socket.");
    exit(1);
  } /* end - if */

  server.sin_family=AF_INET;
  server.sin_port=htons(conf->port);    
  server.sin_addr.s_addr=INADDR_ANY;
  memset(&(server.sin_zero), '\0', 8);
    
  if( bind(socketfd, (struct sockaddr *)&server,sizeof(server)) ) { /* begin - if */
    log_service(conf, "Error binding the socket.");
    exit(1);
  } /* end - if */

  /* listen to MAX_CLIENTS */ 
  listen(socketfd, conf->max_clients);

  do { /* begin - do while */
    msgsock = accept(socketfd, 0, 0);

    /* cleaning input buffer */
    memset(buf_in, '\0', sizeof(buf_in));

    if( msgsock == -1 ) { /* begin - if */
	log_service(conf, "Error accepting connection.");
    } /* end - if */
    else { /* begin - else */
      msgsize=recv(msgsock, buf_in, (conf->cmd_length)*sizeof(char), 0); /* reading buffer */
      if ( msgsize == -1 ) { /* begin - if */
	log_service(conf, "Error reading the buffer.");
	continue;
      } /* end - if */

      /* checking if the command is a raspistill command to avoid to execute dangerous commands */
      for(i=0;i<sizeof(cmdcheck)-1;i++) { /* begin - for */
        if ( cmdcheck[i] != buf_in[i] ) { /* begin - if */
	    log_service(conf, "The recieved command is not a raspisill command:");
	    log_service(conf, buf_in);
          break;
        } /* end - if */
      } /* end - for */
      
      if ( i < sizeof(cmdcheck) - 1 ) { /* begin - if */
        close(msgsock);
        log_service(conf, "Server closed client connection due to the recieved command is not valid.");
        continue;
      } /* end - if */

      /* getting filename */
      cmdlength = (int)(sizeof(buf_in)/sizeof(char));
      for(i=0;i<cmdlength;i++) { /* begin - for */
        if ( buf_in[i] == '-' && buf_in[i+1] == 'o' && buf_in[i+2] == ' ' ) { /* begin - if */
          filename = (char *)malloc((cmdlength-(i+3))*sizeof(char));
          if ( filename == NULL ) { /* begin - if */
            log_service(conf, "Problem with memory reservation. Exiting.");
          } /* end - if */
          strcpy(filename,buf_in + i + 3);
          break;
        } /* end - if */
      } /* end - for */  

      /* insert \0 in first blank space to get rid of the rest of parameters in case filename is not
         the last parameter */
      for(i=0;filename[i]!='\0';++i) { /* begin - for */
        if ( filename[i] == ' ' ) { /* begin - if */
          filename[i] = '\0';
          break;
        } /* end - if */
      } /* end - for */

      /* executing cmd */
      cmdstatus = system(buf_in);
      if ( cmdstatus != 0 ) {  /* begin - if */
      	log_service(conf, "Error using raspberry pi camera with command:");
	log_service(conf, buf_in);
        continue;
      }  /* end - if */
      log_service(conf, "Executed:");
      log_service(conf, buf_in);

      /* sending picture to client */
      cmdstatus = sending_file_to_client(filename, msgsock, conf);
      sleep(3);
      close(msgsock);
      syslog(LOG_LOCAL3, "Server closed client connection.\n");
    } /* end - else */
  } while (1); /* end - do while */

} /* end - rccd function */

/* function to send a file to a client */

int sending_file_to_client(char *filename, int msgsock, rccd_conf *conf) { /* begin - sending_file_to_client function */

  int res = 1;

  FILE *filefd;

  char *filedata;

  filefd = fopen(filename, "rb");

  if ( filefd == NULL ) { /* begin - if*/
      log_service(conf, "Error opening image/video file:");
      log_service(conf, filename);
      return -1;
  } /* end - if */

  /* allocating memory */
  filedata = (char *)malloc(sizeof(char)*(conf->buffer_size));
  if ( filedata == NULL ) { /* begin - if */
      log_service(conf, "Error allocating memory");
      return -1;
  } /* end - if */

  /* send info to client */
  log_service(conf, "Sending image to client.");
  while ( !feof(filefd) ) { /* begin - while */
    memset(filedata, '\0', (conf->buffer_size)*sizeof(char));
    res = fread(filedata, sizeof(char), conf->buffer_size, filefd);
    res = send(msgsock, filedata, res*sizeof(char), 0);
    if ( res == -1 ) { /* begin - if */
      log_service(conf, "Error writing to socket.");
      fclose(filefd);
      free(filedata);
      return res;
    } /* end - if */ 
  } /* end - while */
  log_service(conf, "Image sent to client.");
  /* freeing resources */
  fclose(filefd);
  free(filedata);

  return res;

} /* end - sending_file_to_client function */
