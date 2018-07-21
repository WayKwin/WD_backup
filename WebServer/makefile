.PHONY:clean
WORKDIR=.
VPATH= ./src
CC=clang++ 
CFLGS= -Wall -g -I$(WORKDIR)/incl/ -std=c++11 
#LIBFLAG=.

BIN= WK_Http

all:$(BIN)


WK_Http:locker.o http_conn.o threadpool.o main.o log.o
	$(CC) -lpthread  $^ -o $@ 
%.o:%.c
	$(CC) $(CFLGS) -c $< -o $@	

clean:
	rm -rf *.o $(BIN) 
