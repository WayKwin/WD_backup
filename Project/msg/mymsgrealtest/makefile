# Makefile 
.SUFFIXES:
.SUFFIXES:  .c .o

all: testmsgreal


CC	= clang


WORKDIR=.
LIBDIR=/home/waykwin/WorkSpace/Project/msg/lib
LIBS = -L$(LIBDIR) -lmessagereal
OUTDIR=$(HOME)/bin

INCLDIR=$(WORKDIR)/incl
INCLFLG= -I$(WORKDIR)/incl
CFLAG= $(INCLFLG) -g -c -Wall

VPATH = $(WORKDIR)/src

OBJ1 =keymng_msg_test.o  

testmsgreal:$(OBJ1)
	$(CC) $(LIBS) $^ -o $@ 
	
.c.o:
	$(CC) $(CFLAG) $< 

#.o:.c 1.c 2.c
#	gcc 	-I./incl  -g -c $< -Wall
#	gcc 	-I./incl  -g -c 1.c -1.o -Wall
#	gcc 	-I./incl  -g -c 2.c -2.o -Wall

.PHONY:clean
clean:
	rm *.o
	rm testmsgreal
	rm *.ber
	rm *.txt
	


