/* (c) 2013 jadebustos <jadebustos@gmail.com>                   */
/*     Distributed under GNU GPL v2 License                   */
/*     See COPYING.txt for more details                       */

#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <syslog.h>

extern char *config_file_name;

/* function to process args           */
/* this function processes arguments: */

/* Usage:                             */
/*        rccd --config-file filename */

/* filename is stored in config_file_name */

/* a non zero value is returned if no     */
/* argument is found                      */

int processing_args(int argc, char *argv[]) { /* begin - processing_args function */

    int opt = 0,
	long_index = 0,
	config_file = -1,
	rc = -1;

    /* arguments */
    static struct option long_options[] = {
	{"config-file", required_argument, 0, 'c'},
	{0            , 0                , 0, 0}
    };

    while ( (opt = getopt_long(argc, argv, "apl:b:", long_options, &long_index)) != -1 ) { /* begin - while getopt_long */

	switch(opt) { /* begin - switch */
	case 'c':
	    config_file = 0;
	    /* char strings ends with '\0' */
            config_file_name = (char *)calloc(strlen(optarg) + 1, sizeof(char));
	    if ( config_file_name == NULL ) { /* begin - if */
		syslog(LOG_LOCAL3,"\nAllocation memory error storing configuration file name.\n");
		exit(1);
	    } /* end - if */
	    strcpy(config_file_name, optarg);
	    rc = 0;
	    break;
	} /* end - switch */

    } /* end - while getopt_long */

    return rc;

} /* end - processing_args function */
