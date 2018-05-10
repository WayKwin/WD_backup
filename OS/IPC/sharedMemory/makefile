cc = gcc
all:server client
server:server.c comm.c
	$(cc) $^ -o $@ -g
client:client.c comm.c
	$(cc) $^ -o $@ -g
clean:
	rm -rf server client
.PHONEY:clean all 
