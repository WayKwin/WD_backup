.PHONEY: clean
all:service client
service:SERVER_UDP.c
	gcc $^ -o $@ -g
client:CLIENT_UDP.c
	gcc $^ -o $@ -g
clean: 
	rm -rf service client
