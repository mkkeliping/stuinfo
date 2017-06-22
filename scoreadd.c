#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"
//char * headname = "head.html";
//char * footname = "footer.html";
int cgiMain()
{
	//FILE * fd;
	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
	char stuID[32] = "\0";
	char Cno[32] = "\0";
	char Grade[8]="\0";
	int status = 0;
	/*char ch;
	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
	if(!(fd = fopen(headname, "r"))){
		fprintf(cgiOut, "Cannot open file, %s\n", headname);
		return -1;
	}
	ch = fgetc(fd);

	while(ch != EOF){
		fprintf(cgiOut, "%c", ch);
		ch = fgetc(fd);
	}
	fclose(fd);*/
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


	/*strcpy(sql, "create table Student(stuID smallint primary key,stuName varchar(10) not null,stuSex  char(2) check(stuSex in('男','女')),stuBorn date,stuPolSta varchar(8),stuAdr varchar(30),stutel char(11),stumajor smallint,foreign key (stumajor) references Major(MajorCode))");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		if (ret != 1)
		{
			fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
			mysql_close(db);
			return -1 ;
		}
	}
*/


	sprintf(sql, "insert into SC values(%d, %d,%d)", atoi(stuID),atoi(Cno),atoi(Grade));
	if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
	{
		fprintf(cgiOut, "%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	fprintf(cgiOut, "add student score ok!\n");
	mysql_close(db);
	return 0;
}
