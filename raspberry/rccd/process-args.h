/* (c) 2013 jadebustos <jadebustos@gmail.com> */
/*     Distributed under GNU GPL v2 License                   */
/*     See COPYING.txt for more details                       */

#ifndef PROCESSARGS_H
   #define PROCESSARGS_H

   /* function to process args           */
   /* this function processes arguments: */

   /* Usage:                             */
   /*        rccd --config-file filename */

   /* filename is stored in config_file_name */

   /* a non zero value is returned if no     */
   /* argument is found                      */
   int processing_args(int argc, char *argv[]);
#endif
