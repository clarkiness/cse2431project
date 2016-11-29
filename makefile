OBJS1 = keylog.h client_send.c keylog.c
OBJS2 = server.o
CC = gcc

all : logger server clean

server : $(OBJS2)
	$(CC) $(OBJS2) -o server

logger : $(OBJS1)
	$(CC) $(OBJS1) -o logger

clean:
	\rm *.o