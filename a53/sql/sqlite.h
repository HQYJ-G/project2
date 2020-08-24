/*
 * Name : sqlite.h
 * Date : 2020年8月7日
 * Description : 数据库增删改查
 * Author : 熊涛
 * Version : V1.0
 * Modification:
 *
*/


#ifndef __SQLITE_H__
#define __SQLITE_H__

#include"sqlite3.h"
#include<stdio.h>

#define CMDLEN 128

sqlite3* open_sqlite(const char *s);
void close_sqlite(sqlite3 * db);
int CreateTable(sqlite3 *db,const char * TableName,const char * ColumnName);
int Select(sqlite3 *db, const char * TableName, const char * Pos);
int callbask(void *data, int argc, char **argv, char **azColName);
int Insert(sqlite3 *db, const char *TableName, const char *ColumnName,const char *Value);

#endif
