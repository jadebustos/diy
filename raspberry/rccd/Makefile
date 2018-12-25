CC=gcc

all: rccd.o process-args.o read-config.o mysignal.o log-service.o
	$(CC) raspy-cam-controller.c process-args.o read-config.o rccd.o mysignal.o log-service.o -o rccd -lconfig 

rccd:
	$(CC) -c rccd.c 

process-args:
	$(CC) -c process-args.c

read-config:
	$(CC) read-config.c -o read-config

log-service:
	$(CC) log-service.c -o log-service

mysignal:
	$(CC) mysignal.c -o mysignal 

rccd-client:
	$(CC) rccd-client.c -o rccd-client

clean:
	rm -f *.o *~ rccd rccd-client
