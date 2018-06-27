.PHONEY:clean
insertData: insertData.c
	gcc $^ -o $@ -I ./mysql-connector-c/include  -L ./mysql-connector-c/lib -lmysqlclient 
	export LD_LIBARAY_PATH=./mysql-connector-c/lib
