/* (c) 2013 jadebustos <jadebustos@gmail.com>                   */
/*     Distributed under GNU GPL v2 License                   */
/*     See COPYING.txt for more details                       */

#include <stdlib.h>
#include <libconfig.h>
#include <syslog.h>

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "rccd.h"

extern char *config_file_name;

int read_configuration(rccd_conf *conf) { /* begin - read_configuration function */

    config_t cfg; /* structure to store all config parameters */

    const char *tmp_pidfile;

    /* config initialization */
    config_init(&cfg);

    /* read configuration. If there is an error, report it and exit. */
    if (!config_read_file(&cfg, config_file_name)) { /* begin - if */
	printf("\nConfiguraTion file: %s\n", config_error_file(&cfg));
	printf("\nFile error line: %s\n", config_error_line(&cfg));
	printf("\nConfiguration error text: %s\n", config_error_text(&cfg));
	config_destroy(&cfg);
	exit(100);
    } /* end - if */

    /* Get the pid file name */ 
    if (!config_lookup_string(&cfg, "pid", &tmp_pidfile)) { /* begin - if */
	printf("\nNo pidfile in configuration.\n");    
	exit(1);
    } /* end - if */

    conf->pidfile = (char *)calloc(strlen(tmp_pidfile) + 1, sizeof(char));
    if ( conf->pidfile == NULL ) { /* begin - if */
	printf("\nAllocation memory error storing pid file.\n");
        exit(1);
    } /* end - if */
    strcpy(conf->pidfile, tmp_pidfile);

    /* get log service */
    if (!config_lookup_int(&cfg, "log_service", &conf->log_service)) { /* begin - if */
	printf("\nNo log service in configuration.\n");    
	exit(3);
    } /* end - if */

    /* get the port */
    if (!config_lookup_int(&cfg, "port", &conf->port)) { /* begin - if */
	printf("\nNo port in configuration.\n");    
	exit(3);
    } /* end - if */

    /* get max_clients */
    if (!config_lookup_int(&cfg, "max_clients", &conf->max_clients)) { /* begin - if */
	printf("\nNo max_clients in configuration.\n");    
	exit(4);
    } /* end - if */

    /* get cmd_length */  
    if (!config_lookup_int(&cfg, "cmd_length", &conf->cmd_length)) { /* begin - if */
	printf("\nNo cmd_length in configuration.\n");    
	exit(5);
    } /* end - if */

    /* get buffer_size */
    if (!config_lookup_int(&cfg, "buffer_size", &conf->buffer_size)) { /* begin - if */
	printf("\nNo buffer_size in configuration.\n");    
	exit(6);
    } /* end - if */

    /* destroy configuration */
    config_destroy(&cfg);

    return 0;

} /* end - read_configuration function */
