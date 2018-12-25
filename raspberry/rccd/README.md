# Raspberry Pi Camera Daemon (rccd)

## WHAT IS rccd-c-server?

  rccd stands for Raspberry Pi Camera daemon.

  This daemon intends to be a simple daemon to introduce how to develop
  in C using Raspberry Pi and its camera as a way to catch your eye.

  rccd is listening waiting to someone sends a command to activate
  Raspberry Pi camera, and them send back the picture to the client.

  There is no authentication of the client and I am pretty sure that
  there are a lot of improvements that you could do it ;-).

## ON WHAT HARDWARE DOES IT RUN?

  This version is able to run on whatever hardware in which an ANSI C
  compiler could be used.

  This daemon only executes a command and then open a picture to send
  it to the client. The filename of this picture is hardcoded, (just
  another improvement to be done ;-)).

## CONFIGURATION

  The only configuration that need to be done is to redirect local3
  rsyslog facility to a file. To do that you need to add:

    local3.*	/var/log/rccd.log

  to /etc/rsyslog.conf and restart rsyslog.

  Afther that all logging info will be recorded in /var/log/rccd.log
  file.
_____________________________________________________________________
 (c) 2013 jadebustos <jadebustos@gmail.com>
     Distributed under GNU GPL v2 License
     See COPYING.txt for more details
