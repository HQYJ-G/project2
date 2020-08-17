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

#include<sqlite3.h>
#include<iostream>
#include<queue>
#include<stdio.h>

using namespace std;

typedef struct
{
    string key;
    string val;
    int num;
}sBufType;



class cSqlite
{
	private:
		sqlite3 *db;
        int Result;
        char * ErrMsg;
        static int callbask(void *data, int argc, char **argv, char **azColName);

	public:

        queue<sBufType> Buf;

        cSqlite(const string s);
        ~cSqlite();
        int CreateTable(const string TableName,const string ColumnName);
        int Select(const string TableName, const string Pos);
        int Insert(const string TableName, const string ColumnName,const string Value);
        int Updata(const string TableName, const string Pos,const string KeyVal);
        int Delect(const string TableName, const string Pos);
        int CleanBuf(void);
        int QueueOut(sBufType &Buf);
};

int CreateInfo(void);
#endif
