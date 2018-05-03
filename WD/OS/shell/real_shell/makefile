.PHONEY:clean make
ver = d
ifeq ($(ver),d)
OBJ = parsing
flag += -DDEBUG  -DDEBUG_PARSING -g
SRC = read_command.c type_prompt.c parsing.c
else ifeq ($(ver),r)
OBJ = shell
SRC = shell.c read_command.c type_prompt.c parsing.c 
flag = -g;
endif
$(OBJ):
	gcc  $(SRC) -o $(OBJ)  -lreadline -L /usr/lib64/ $(flag) 
clean:
	rm -rf $(OBJ)
