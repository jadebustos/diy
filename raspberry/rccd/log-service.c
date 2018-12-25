/* (c) 2013 jadebustos <jadebustos@gmail.com>                   */
/*     Distributed under GNU GPL v2 License                   */
/*     See COPYING.txt for more details                       */

#include <stdio.h>
#include <syslog.h>

#include "rccd.h"

/* function to send information to system log */

/* rccd_conf *conf -> configuration                          */
/* char *msg -> message to send to the log system            */

void log_service (rccd_conf *conf, char *msg) { /* begin - log_service function */

    switch(conf->log_service) { /* begin - switch */
    case 0:
	openlog("rccd daemon",LOG_NOWAIT|LOG_PID,LOG_DAEMON);
	syslog(LOG_LOCAL3, msg); 
	closelog();
	break;
    case 1:
	printf("systemd\n");
	break;
    default:
	printf("default\n");
	break;
    } /* end - switch */

} /* end - log_service function */
