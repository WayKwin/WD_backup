.PHONEY:bst clean
bst:test.cpp tree.cpp
	g++ -g $^ -o $@ -D __DEBUG__DELETENODE__  -D __DEBUG__DELETEMIN__
clean:
	rm -rf bst
