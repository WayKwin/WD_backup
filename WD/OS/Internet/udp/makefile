.PHONEY: clean
all:service client
service:SERVER_UDP.c
	gcc -static $^ -o $@
client:CLIENT_UDP.c
	gcc -static $^ -o $@
clean:
	rm -rf service client
