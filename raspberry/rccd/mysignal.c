/* (c) 2013 jadebustos <jadebustos@gmail.com> */
/*     Distributed under GNU GPL v2 License                   */
/*     See COPYING.txt for more details                       */

#include <syslog.h>
#include <signal.h>
#include <stdlib.h>

/* function to handle signals */

void signal_handler(int signal) { /* begin - signal_handler */

  /* openning a connection to the syslog server */
  openlog("rccd daemon",LOG_NOWAIT|LOG_PID,LOG_DAEMON);

  syslog(LOG_LOCAL3, "Caught %s signal. Exiting.\n", strsignal(signal));
  exit(1);

  return;

} /* end - signal_handler */
