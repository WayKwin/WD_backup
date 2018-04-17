.PHONEY:clean test
obj = maze
src = maze.c
$(obj):$(src)
	gcc $^ -o $@ -g -DLOOP
clean:
	rm -rf test

