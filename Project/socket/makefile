.PHONY:clean all

WORKDIR=.


CC=gcc
CFLGS= -Wall -g -I$(WORKDIR)/
LIBFLAG = -L$(HOME)/WorkSpace/Project/socket

BIN=srv myclient  myserver myclient2 myclient3 myclient4 client4

all:$(BIN)

	
srv:srv.o
	$(CC) $(LIBFLAG)  -lpthread -litcastsocket $^ -o $@ 
	

myserver:myserver.o
	$(CC) $(LIBFLAG)  -lpthread -litcastsocket $^ -o $@ 
	
myclient:myclient.o
	$(CC) $(LIBFLAG)  -lpthread -litcastsocket $^ -o $@ 
		

	
myclient2:myclient2.o
	$(CC) $(LIBFLAG)  -lpthread -litcastsocket $^ -o $@ 
	
myclient3:myclient3.o
	$(CC) $(LIBFLAG)  -lpthread -litcastsocket $^ -o $@ 	
	
myclient4:myclient4.o
	$(CC) $(LIBFLAG)  -lpthread -litcastsocket $^ -o $@ 

client4:client4.o
	$(CC) $(LIBFLAG)  -lpthread -litcastsocket $^ -o $@ 

			
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@	

clean:
	rm -f *.o $(BIN)




