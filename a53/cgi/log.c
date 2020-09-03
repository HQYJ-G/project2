#include"cgic.h"
#include"common.h"
#include"sqlite.h"
#include"sqlite3.h"

sqlite3 * html_open_sqlite(const char *s)
{

	int Result;
	sqlite3 *db;

    Result = sqlite3_open(s,&db);

    if (Result == 0)
    {
//        fprintf(cgiOut,"<p>open sql success</p>\n");
    }else
    {
        fprintf(cgiOut,"<p>open sql error</p>\n");
    }

	return db;

}


int html_callbask(void *data, int argc, char **argv, char **azColName)
{
    int i;

	fprintf(cgiOut,"<tr>");

    for(i=0; i < argc; i++)
    {
		fprintf(cgiOut,"<td>%s</td>",argv[i]?argv[i]:"NULL");
    }

	fprintf(cgiOut,"</tr>\n");
    return 0;
}

int html_select(sqlite3 *db,const char * TableName)
{

	int Result;
    char sqlcmd[128];
	char * ErrMsg;

    if (db == NULL)
    {
        fprintf(cgiOut,"<p>db is NULL</p>\n");
        return -1;
    };

	sprintf(sqlcmd,"SELECT * FROM %s ;",TableName);
    Result = sqlite3_exec(db,sqlcmd,html_callbask,NULL,&ErrMsg);

    if(Result == 0)
	{
//		fprintf(cgiOut,"<p> Select table success</p>\n");
	}else
	{	
		fprintf(cgiOut,"<p> Select table error</p>\n");
		return -1;
	}

	return 0;

}

int cgiMain()
{
	sqlite3 *db;
	int Result;


	cgiHeaderContentType("text/html");
	fprintf(cgiOut,"<HTML><HEAD>\n");
	fprintf(cgiOut,"<meta charset =\"utf-8\">\n");
	fprintf(cgiOut,"<TITLE>日志</TITLE></HEAD>\n");
	fprintf(cgiOut,"<BODY><H1>日志</H1>\n");
	db = html_open_sqlite("/project2/log");

	fprintf(cgiOut,"<h>操作历史</h>");
	fprintf(cgiOut,"<table border=\"1\">");
	fprintf(cgiOut,"<tr>");
	fprintf(cgiOut,"<th>序号</th>");
	fprintf(cgiOut,"<th>命令</th>");
	fprintf(cgiOut,"<th>日期</th>");
	fprintf(cgiOut,"</tr>");
	html_select(db,"cmd");
	fprintf(cgiOut,"</table>");
	fprintf(cgiOut,"<p>                </p>");
	fprintf(cgiOut,"<h>传感器历史</h>");
	fprintf(cgiOut,"<table border=\"1\">");
	fprintf(cgiOut,"<tr>");
	fprintf(cgiOut,"<th>序号</th>");
	fprintf(cgiOut,"<th>温度</th>");
	fprintf(cgiOut,"<th>湿度</th>");
	fprintf(cgiOut,"<th>日期</th>");
	fprintf(cgiOut,"</tr>");
	html_select(db,"env_data");
	fprintf(cgiOut,"</table>");

	fprintf(cgiOut,"<a href = \"/index.html\"> back </a>\n");
	fprintf(cgiOut,"</BODY>\n");
	fprintf(cgiOut,"</HTML>\n");

	sqlite3_close(db);
}
