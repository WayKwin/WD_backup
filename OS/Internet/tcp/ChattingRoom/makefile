.PHONEY:clean
all:service client

service:service.cpp
	clang++ $^ -o $@ -g
client:client.cpp
	clang++ $^ -o $@ -g
clean:
	rm -rf client service
