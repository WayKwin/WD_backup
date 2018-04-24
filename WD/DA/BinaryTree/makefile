.PHONEY:clean
CC=clang
OBJ=UnitTestBinary
#SRC=UnitTest_BinaryTree.c BinaryTree.c
SRC = BinaryTree.c
FLAGS= -g -D__QUEUE_FOR_TREE__
$(OBJ):$(SRC)
	$(CC) $(SRC) -o $(OBJ) $(FLAGS)
clean:
	rm -rf $(OBJ)

