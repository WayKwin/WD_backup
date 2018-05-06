.PHONEY: clean
all:service clinet
service: SERVER_TCP_A.c
	gcc $^  -o $@  -lpthread
clinet: CLINET_TCP.c
	gcc $^  -o $@ 
clean:
	rm-rf service clinet
