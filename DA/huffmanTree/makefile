.PHONEY:clean
method=clang++
FLAGS=-g -D __DEBUG__ -std=c++11
filecompress:filecompress.cpp
	$(method) $^ -o $@  $(FLAGS)
clean:
	rm -rf filecompress

