.PHONEY: clean
all:service clinet
service: SERVER_TCP.c
	gcc $^  -o $@ 
clinet: CLINET_TCP.c
	gcc $^  -o $@ 
clean:
	rm-rf service clinet
