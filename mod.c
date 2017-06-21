#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
	char stuID[32] = "\0";
	char stuName[32] = "\0";
	char stuSex[8]="\0";
	char stuBorn[15]="\0";
	char stuPolSta[8]="\0";
	char stuAdr[30]="\0";
	char stutel[15]="\0";
	char stumajor[16] = "\0";
	int status = 0;
	status = cgiFormString("stuID",  stuID, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuId error!\n");
		return 1;
	}
	status = cgiFormString("stuName",  stuName, 32);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuName error!\n");
		return 1;
	}
	status = cgiFormString("stuSex",  stuSex, 8);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuSex error!\n");
		return 1;
	}
	status = cgiFormString("stuBorn",  stuBorn, 15);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuBorn error!\n");
		return 1;
	}
	status = cgiFormString("stuPolSta",  stuPolSta, 8);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuPolSta error!\n");
		return 1;
	}
	status = cgiFormString("stuAdr",  stuAdr, 30);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get stuAdr error!\n");
		return 1;
	}

	status = cgiFormString("stutel",  stutel, 15);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get  stutel error!\n");
		return 1;
	}
	status = cgiFormString("stumajor", stumajor, 16);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get  stumajor error!\n");
		return 1;
	}


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

	sprintf(sql, "update Student set stuName='%s', stuSex= '%s',stuBorn= '%s', stuPolSta='%s',stuAdr='%s',stutel='%s',stumajor= %d where stuID = %d ", stuName,stuSex,stuBorn,stuPolSta,stuAdr,stutel,atoi(stumajor),atoi(stuID));
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return ;
	}



	fprintf(cgiOut, "update student ok!\n");
	mysql_close(db);
	return 0;
}
