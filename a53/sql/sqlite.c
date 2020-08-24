/*
 * Name : sqlite.c
 * Date : 2020年8月7日
 * Description : 数据库 实现Sqlite增删该查
 * Author : 熊涛
 * Version : V1.0
 * Modification:
 *
*/

#include "sqlite.h"
#include "string.h"
#include "stdio.h"
#include "cgic.h"
/*
  *名称：      open_sqlite
  *功能：      打开数据库
  * 参数：     const string s 数据库名字
  * 返回值： 无
*/
sqlite3* open_sqlite(const char *s)
{
	int Result;
	sqlite3 *db;

    Result = sqlite3_open(s,&db);

    if (Result == 0)
    {
        printf("open sql success\n");
    }else
    {
        printf("open sql error %d\n",Result);
    }

	return db;

};

/*
  * 名称：   close_sqlite
  * 功能：   关闭数据库
  * 参数：   无
  * 返回值： 无
*/
void close_sqlite(sqlite3 * db)
{
    if (db != NULL)
    {
        sqlite3_close(db);
    }
};

/*
  *名称：      CreateTable
  *功能：      创建一个表
  * 参数：     TableName 表名；ColumnName列名+类型(e.g. " ID INTEGER PRIMARY KEY   AUTOINCREMENT,NAME TEXT NOT NULL,AGE INT")
  * 返回值： 成功返回0；失败返回-1
*/
int CreateTable(sqlite3 *db,const char * TableName,const char * ColumnName)
{
	int Result;
    char sqlcmd[CMDLEN];
	char * ErrMsg;

    if (db == NULL)
    {
        printf("db is NULL\n");
        return -1;
    }
	
	sprintf(sqlcmd,"CREATE TABLE %s ( %s );",TableName,ColumnName);

    Result = sqlite3_exec(db,sqlcmd,NULL,NULL,&ErrMsg);
    if(Result == 0)
    {
        printf("create table success\n");
    }else
    {
        printf("create table failed:%s\n",ErrMsg);
        return -1;
    }

    return 0;
};

/*
  *名称：      Select
  *功能：      从指定的表中查找数据
  * 参数：      TableName 表名； Pos查找的目标 （e.g."ColumnName = Value"）
  * 返回值： 成功返回0；失败返回-1
*/
int Select(sqlite3 *db, const char * TableName, const char * Pos)
{
	int Result;
    char sqlcmd[128];
	char * ErrMsg;

    if (db == NULL)
    {
        printf("db is NULL\n");
        return -1;
    };


//	sprintf(sqlcmd,"SELECT * FROM %s WHERE \"%s\" ;",TableName,Pos);

	sprintf(sqlcmd,"SELECT * FROM %s ;",TableName);
    Result = sqlite3_exec(db,sqlcmd,callbask,NULL,&ErrMsg);

    if(Result == 0)
    {
        printf("Select table success\n");
    }else
    {
        printf("Select table failed:%s\n",ErrMsg);
        return -1;
    }


    return 0;
};

/*
  *名称：      callbask
  *功能：      sqlite3_exec执行select的回调函数
  * 参数：
  * 返回值：
*/
int callbask(void *data, int argc, char **argv, char **azColName)
{
    int i;


//	fprintf(cgiOut,"<p>");

    for(i=0; i < argc; i++)
    {
//		fprintf(cgiOut,"%s|",argv[i]?argv[i]:"NULL");
		printf("%s %s \n",azColName[i],argv[i]?argv[i]:"NULL");
    }

//	fprintf(cgiOut,"</p>\n");
    return 0;
}

/*
  *名称：      Insert
  *功能：      向指定表插入记录
  * 参数：     const string TableName 表名；const string ColumnName列名；onst string Value列对应的值
  * 返回值： 成功返回0；失败返回-1
*/
int Insert(sqlite3 *db, const char *TableName, const char *ColumnName,const char *Value)
{
	int Result;
    char sqlcmd[128];
	char * ErrMsg;

    if (db == NULL)
    {
        printf("db is NULL\n");
        return -1;
    };
	
	sprintf(sqlcmd,"INSERT INTO %s ( %s ) VALUES ( %s );",TableName,ColumnName,Value);

	printf("%s\n",sqlcmd);

    Result = sqlite3_exec(db,sqlcmd,NULL,NULL,&ErrMsg);
    if(Result == 0)
    {
        printf("Insert table success\n");
    }else
    {
        printf("Insert table failed:%s\n",ErrMsg);
        return -1;
    }

    return 0;
};


