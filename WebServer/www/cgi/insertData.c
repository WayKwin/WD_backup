#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"mysql-connector-c/include/mysql.h"
void insert_data(char* name,char*sex,char*age,char* telphone)
{
  MYSQL* mysql_fd = mysql_init(NULL);
  if(mysql_real_connect(mysql_fd,"127.0.0.1","root","","people",3306,NULL,0) == NULL)
  {
    goto out;
  }
  /*printf("connect mysql success!\n");*/

  char sql[1024];

  sprintf(sql,"INSERT INTO people_info (name,sex,brithday,telphone) VALUES (\"%s\",\"%s\",\"%s\",\"%s\")",name,sex,age,telphone);
  printf("%s",sql);
 if( mysql_query(mysql_fd,sql)!=  0)
 {
   /*printf("%d:%s\n",mysql_errno(mysql_fd),mysql_error(mysql_fd));*/
 }
out:
  //mysql_free_result(result);
  mysql_close(mysql_fd);
  mysql_library_end();
}
int main()
{
  /*char info[1024] = "name=Jack&sex=male&age=1990-1-1&telphone=12345678901";*/
    /*[>strcpy(info,getenv("QUERY_STRING"));<]*/
    /*char* name = strtok(info,"=");*/

  //name=Jack&sex=male&age=1990-1-1&telphone=12345678901
  char* method =  getenv("METHOD");
  char* name = NULL;
  char* sex = NULL;
  char* age = NULL;
  char* tel = NULL;
  if(strcmp(method,"GET") == 0)
  {
    char  info[1024];
    printf("got info%s",getenv("QUERY_STRING"));
    strcpy(info,getenv("QUERY_STRING"));
    strtok(info,"=&");
    name = strtok(NULL,"=&");

    strtok(NULL,"=&");
    sex= strtok(NULL,"=&");

    strtok(NULL,"=&");
    age= strtok(NULL,"=&");

    strtok(NULL,"=&");
    tel= strtok(NULL,"=&");
    insert_data(name,sex,age,tel);
    
  }
  else if(strcmp(method,"POST") == 0)
  {
    //读取长度
    /*char* content_length = getenv("CONTENT_LENGTH");*/

  }
  /*insert_data("Jack","male","20","13891671774");*/
  return 0;
}

