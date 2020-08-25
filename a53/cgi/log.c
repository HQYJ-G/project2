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
        fprintf(cgiOut,"<p>open sql success</p>\n");
    }else
    {
        fprintf(cgiOut,"<p>open sql error</p>\n");
    }

	return db;

}


int html_callbask(void *data, int argc, char **argv, char **azColName)
{
    int i;

	fprintf(cgiOut,"<p>|");

    for(i=0; i < argc; i++)
    {
		fprintf(cgiOut,"%-5s|",argv[i]?argv[i]:"NULL");
    }

	fprintf(cgiOut,"</p>\n");
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
		fprintf(cgiOut,"<p> Select table success</p>\n");
	}else
	{	
		fprintf(cgiOut,"<p> Select table success</p>\n");
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
	fprintf(cgiOut,"<TITLE>操作历史</TITLE></HEAD>\n");
	fprintf(cgiOut,"<BODY><H1>操作历史</H1>\n");
	db = html_open_sqlite("/project2/log");
	fprintf(cgiOut,"<p>------------------------</p>");
	fprintf(cgiOut,"<p>|ID|CMD|DATE|</p>");
	html_select(db,"cmd");
	fprintf(cgiOut,"<p>------------------------</p>");

	fprintf(cgiOut,"<a href = \"/index.html\"> back </a>\n");
	fprintf(cgiOut,"</BODY>\n");
	fprintf(cgiOut,"</HTML>\n");

	sqlite3_close(db);
}
