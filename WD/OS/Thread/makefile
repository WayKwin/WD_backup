.PHONEY:clean
ver = j
#注意ifeq 后要有一个空格
ifeq ($(ver),j)
OBJ=Join_detach
SRC=Join_detach.c
else ifeq ($(ver),m)
OBJ=Mutex
SRC=mutex.c
else ifeq ($(ver),p)
OBJ=model
SRC=p_c_model.c
endif
$(OBJ):$(SRC)
	gcc  $^ -o $@  -lpthread
