/* (c) 2013 jadebustos <jadebustos@gmail.com> */
/*     Distributed under GNU GPL v2 License                   */
/*     See COPYING.txt for more details                       */

#ifndef RCCD_H
  #define RCCD_H
  /* configuration data */
  typedef struct {
    char *pidfile; /* default pid file */
    int port, /* default port */
        max_clients, /* default max_clients */
        cmd_length, /* default cmd_length (bytes) */
	log_service, /* log service */
        buffer_size; /* default buffer_size (bytes) */
  } rccd_conf;
  void rccd (rccd_conf *conf);
  int sending_file_to_client(char *filename, int msgsock, rccd_conf *conf);
#endif
