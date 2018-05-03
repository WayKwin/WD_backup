.PHONEY:clean
all: service client
service:service.c
	gcc $^ -o $@ -g
client: client.c
	gcc $^ -o $@ -g
clean:
	rm -rf service client
