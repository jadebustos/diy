/* 
   Raspberry pi Camera C Daemon or rccd
 */

/* (c) 2013 jadebustos <jadebustos@gmail.com>                   */
/*     Distributed under GNU GPL v2 License                   */
/*     See COPYING.txt for more details                       */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

#include "rccd.h"
#include "mysignal.h"
#include "log-service.h"

char *config_file_name;

int main(int argc, char* argv[]) { /* begin - main function */

    pid_t pid = 0;
    pid_t sid = 0;

    FILE *pidfd;

    int rc = 0;

    rccd_conf myconf;

    /* intercepting signals to log exit */
    signal(SIGKILL, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGPIPE, signal_handler);

    /* processing arguments */
    rc = processing_args(argc, argv);  

    /* finish if no config-file is passed as argument */
    if ( rc != 0 ) { /* begin - if */
	printf("No configuration file passed as argument.\n");
	printf("Usage: rccd --config-file filename\n");
	exit(1);
    } /* end - if */

    /* reading configuration */  
    rc = read_configuration(&myconf);  

    exit(0);

    pid = fork(); /* child process creation */

    if ( pid < 0 ) { /* begin - if */
	log_service(&myconf,"Fork process failed.");
	exit(1);
    } /* end - if */

    /* killing father process */
    if ( pid > 0 ) { /* begin - if */
	exit(0);
    } /* end - if */

    /* unmasking the file mode */
    umask(0);

    /* setting new session id */
    sid = setsid();

    if( sid < 0 ) { /* begin - if */
	log_service(&myconf,"Fork process failed.");
	exit(1);
    } /* end - if */

    /* writing pid to a file */
    pidfd = fopen(myconf.pidfile, "w");
    if ( pidfd == NULL ) { /* begin - if */
       	log_service(&myconf,strcat(strcat("File ", myconf.pidfile), " could not be opened. Exiting."));
	exit(1);
    } /* end - if */

    fprintf(pidfd, "%d", sid);
    fclose(pidfd);

    /* setting current working directory to root */
    chdir("/");

    /* closing stdin. stdout and stderr */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    log_service(&myconf, "rccd started.");

    while (1) { /* begin - while */
	sleep(1);
	rccd(&myconf);
    } /* end - while */

    return (0);
} /* end - main function */
