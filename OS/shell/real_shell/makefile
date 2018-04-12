.PHONEY:clean
flags_read_command += -Ddebug -Ddebug_read_command
flags += -DSTRUCT_PARSE_INFO  -Ddebug
OBJ = parsing
$(OBJ): read_command.c type_prompt.c parsing.c
	gcc -o $@ $^ -lreadline -L /usr/lib64/ $(flags)
clean:
	rm -rf $(OBJ)
