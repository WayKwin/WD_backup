.PHONY:clean

http:locker.cpp http_conn.cpp  threadpool.cpp main.cpp 
	clang++ $^ -o $@  -g -lpthread
clean:
	rm -rf http
