.PHONEY:clean
method=clang++
FLAGS=-g -D __DEBUG__
filecompress:filecompress.cpp
	$(method) $^ -o $@  $(FLAGS)
clean:
	rm -rf filecompress

