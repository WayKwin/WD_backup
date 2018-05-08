.PHONEY:clean
CC=clang
OBJ=UnitTestBinary
#SRC=UnitTest_BinaryTree.c BinaryTree.c
SRC = BinaryTree.c UnitTest.c
FLAGS= -g 
$(OBJ):$(SRC)
	$(CC) $(SRC) -o $(OBJ) $(FLAGS)
clean:
	rm -rf $(OBJ)

