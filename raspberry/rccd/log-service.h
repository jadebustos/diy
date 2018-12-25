/* (c) 2013 jadebustos <jadebustos@gmail.com>                   */
/*     Distributed under GNU GPL v2 License                   */
/*     See COPYING.txt for more details                       */

#include "rccd.h"

#ifndef LOGSERVICE_H
  #define LOGSERVICE_H
  /* function to send information to system log */

  /* rccd_conf *conf -> configuration                          */
  /* char *msg -> message to send to the log system            */
  void log_service (rccd_conf *conf, char *msg);
#endif
