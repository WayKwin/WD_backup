.PHONEY:clean
OBJ = parsing
ver = parsing
#ifeq($(ver),parsing)
flag += -DDEBUG  -DDEBUG_PARSING
#else
#flag += -DDEBUG -DDEBUG_READ_COMMAND
#endif
$(OBJ):read_command.c type_prompt.c parsing.c
	gcc -o $@ $^  -lreadline -L /usr/lib64/ $(flag) -g
clean:
	rm -rf $(OBJ)
