.PHONY:clean

http:locker.cpp http_conn.cpp  threadpool.cpp main.cpp log.cpp
	clang++ $^ -o $@  -g -lpthread -std=c++11
clean:
	rm -rf http
