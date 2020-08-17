/*
 * Name : sqlite.cpp
 * Date : 2020年8月7日
 * Description : 数据库 实现Sqlite类中方法
 * Author : 熊涛
 * Version : V1.0
 * Modification:
 *
*/

#include "sqlite.h"

/*
  *名称：      构造函数
  *功能：      打开数据库
  * 参数：     const string s 数据库名字
  * 返回值： 无
*/
cSqlite::cSqlite(const string s)
{
    Result = sqlite3_open(s.c_str(),&db);

    if (Result == 0)
    {
        cout << "open sql success"<<endl;
    }else
    {
        db = NULL;
        cout  << "open sql error"<< Result<<endl;
    }

};

/*
  *名称：      析构函数
  *功能：      关闭数据库
  * 参数：     无
  * 返回值： 无
*/
cSqlite::~cSqlite()
{
    if (Result == 0)
    {
        sqlite3_close(db);
    }
};

/*
  *名称：      CreateTable
  *功能：      创建一个表
  * 参数：     const string TableName 表名；const string ColumnName列名+类型(e.g. " ID INTEGER PRIMARY KEY   AUTOINCREMENT,NAME TEXT NOT NULL,AGE INT")
  * 返回值： 成功返回0；失败返回-1
*/
int cSqlite::CreateTable(const string TableName,const string ColumnName)
{
    string sqlcmd;

    if (db == NULL)
    {
        cout<<"db is NULL"<<endl;
        return -1;
    }

    sqlcmd = "CREATE TABLE " + TableName + "(" + ColumnName + ");";

    Result = sqlite3_exec(db,sqlcmd.c_str(),NULL,NULL,&ErrMsg);
    if(Result == 0)
    {
        cout<<"create table success"<<endl;
    }else
    {
        cout<<"create table failed:"<<ErrMsg<<endl;
        return -1;
    }

    return 0;
};

/*
  *名称：      Select
  *功能：      从指定的表中查找数据
  * 参数：     const string TableName 表名；const string Pos查找的目标 （e.g."ColumnName = Value"）
  * 返回值： 成功返回0；失败返回-1
*/
int cSqlite::Select(const string TableName, const string Pos)
{
    string sqlcmd;

    if (db == NULL)
    {
        cout<<"db is NULL"<<endl;
        return -1;
    };

    sqlcmd = "SELECT  * FROM " + TableName + " WHERE " + Pos +  " ; ";

    cout << sqlcmd <<endl;

    Result = sqlite3_exec(db,sqlcmd.c_str(),cSqlite::callbask,this,&ErrMsg);

    if(Result == 0)
    {
        cout<<"Select table success"<<endl;
    }else
    {
        cout<<"Select table failed:"<<ErrMsg<<endl;
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
int cSqlite::callbask(void *data, int argc, char **argv, char **azColName)
{
    int i;
    sBufType temp;

    cSqlite * t = static_cast<cSqlite * >(data);

    for(i=0; i < argc; i++)
    {
        temp.key = azColName[i];
        temp.val=  argv[i]?argv[i]:"NULL";
        temp.num = argc;
        t->Buf.push(temp);
    }


    return 0;
}

/*
  *名称：      Insert
  *功能：      向指定表插入记录
  * 参数：     const string TableName 表名；const string ColumnName列名；onst string Value列对应的值
  * 返回值： 成功返回0；失败返回-1
*/
int cSqlite::Insert(const string TableName, const string ColumnName,const string Value)
{
    string sqlcmd;

    if (db == NULL)
    {
        cout<<"db is NULL"<<endl;
        return -1;
    };

    sqlcmd = "INSERT INTO  " + TableName + " ( " +  ColumnName + " ) VALUES (" + Value +  " ); ";

    cout<<sqlcmd<<endl;

    Result = sqlite3_exec(db,sqlcmd.c_str(),NULL,NULL,&ErrMsg);
    if(Result == 0)
    {
        cout<<"Insert table success"<<endl;
    }else
    {
        cout<<"Insert table failed:"<<ErrMsg<<endl;
        return -1;
    }

    return 0;
};

/*
  *名称：      Updata
  *功能：      从指定的表中查找数据
  * 参数：     const string TableName 表名；const string Pos查找的目标 （e.g."ColumnName = Value"）；const string KeyVal修改列和值（e.g."key = Value"）
  * 返回值： 成功返回0；失败返回-1
*/
int cSqlite::Updata(const string TableName, const string Pos,const string KeyVal)
{
    string sqlcmd;

    if (db == NULL)
    {
        cout<<"db is NULL"<<endl;
        return -1;
    };

    sqlcmd = "UPDATE " + TableName + " SET " +  KeyVal + " WHERE " + Pos +  " ; ";

    cout<<sqlcmd<<endl;

    Result = sqlite3_exec(db,sqlcmd.c_str(),NULL,NULL,&ErrMsg);
    if(Result == 0)
    {
        cout<<"Updata table success"<<endl;
    }else
    {
        cout<<"Updata table failed:"<<ErrMsg<<endl;
        return -1;
    }

    return 0;
};

/*
  *名称：      Delect
  *功能：      从指定的表中查找数据
  * 参数：     const string TableName 表名；const string Pos查找的目标 （e.g."ColumnName = Value"）
  * 返回值： 成功返回0；失败返回-1
*/
int cSqlite::Delect(const string TableName, const string Pos)
{
    string sqlcmd;

    if (db == NULL)
    {
        cout<<"db is NULL"<<endl;
        return -1;
    };

    sqlcmd = "DELETE FROM  " + TableName + "  WHERE " + Pos + ";";

    Result = sqlite3_exec(db,sqlcmd.c_str(),NULL,NULL,&ErrMsg);
    if(Result == 0)
    {
        cout<<"Delect table success"<<endl;
    }else
    {
        cout<<"Delect table failed:"<<ErrMsg<<endl;
        return -1;
    }
    return 0;
};

/*
  *名称：      CleanBuf
  *功能：      清空缓存
  * 参数：     无
  * 返回值： 成功返回0；
*/
int cSqlite::CleanBuf(void)
{
    while(!Buf.empty())
        Buf.pop();

    return 0;
};

/*
  *名称：      QueueOut
  *功能：      出队
  * 参数：     无
  * 返回值： 成功返回0；失败返回-1；
*/
 int cSqlite::QueueOut(sBufType &Buf)
{
    if(this->Buf.empty())
    {
        return -1;
    }

    Buf = this->Buf.front();
    this->Buf.pop();

    return 0;
};
