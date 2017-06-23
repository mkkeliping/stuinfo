#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"
char * headname = "head.html";
char * footname = "footer.html";
int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
  char stuID[32] = "\0";
	char Cno[32] = "\0";
	char Grade[8]="\0";
	int status = 0;
	FILE * fd;
	char ch;

	//fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
	if(!(fd = fopen(headname, "r"))){
		fprintf(cgiOut, "Cannot open file, %s\n", headname);
		return -1;
	}
	ch = fgetc(fd);

	while(ch != EOF){
		fprintf(cgiOut, "%c", ch);
		ch = fgetc(fd);
	}
fclose(fd);
  status = cgiFormString("stuID",  stuID, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuId error!\n");
		return 1;
	}
	status = cgiFormString("Cno", Cno, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Cno error!\n");
		return 1;
	}
	status = cgiFormString("Grade",  Grade, 8);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Grade error!\n");
		return 1;
	}


	fprintf(cgiOut, "Cno= %s, Grade= %s, stuID = %s\n", Cno, Grade, stuID);


	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

	int ret;
	char sql[128] = "\0";
	MYSQL *db;

	//初始化
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "STU",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	mysql_options(db,MYSQL_SET_CHARSET_NAME,"utf8");

	sprintf(sql, "update SC set Cno= '%s', Grade= %d where stuID = '%s' ", Cno,atoi(Grade),stuID);
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}



	fprintf(cgiOut, "update SC ok!\n");
	fprintf(cgiOut, "<a href=\"/score.html\">返回</a>");
	mysql_close(db);
	return 0;
}
