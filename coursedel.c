
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"
char * headname = "head.html";
char * footname = "footer.html";

int cgiMain()
{
FILE * fd;
	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	char Cno[32] = "\0";

	int status = 0;
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

	status = cgiFormString("Cno",  Cno, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get Cno error!\n");
		return 1;
	}

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

	sprintf(sql, "delete from Course where Cno = '%s'", Cno);
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}
	fprintf(cgiOut, "delete Course ok!\n");
	mysql_close(db);
	fprintf(cgiOut, "<a href=\"/course.html\">返回</a>");

	return 0;
}
