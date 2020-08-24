#include"cgic.h"
#include"common.h"
#include"sqlite.h"

int cgiMain()
{

	cgiHeaderContentType("text/html");
	fprintf(cgiOut,"<HTML><HEAD>\n");
	fprintf(cgiOut,"<meta charset =\"utf-8\">\n");
	fprintf(cgiOut,"<TITLE>操作历史</TITLE></HEAD>\n");
	fprintf(cgiOut,"<BODY><H1>操作历史</H1>\n");
	
	fprintf(cgiOut,"<a href = \"/index.html\"> back </a>\n");
	fprintf(cgiOut,"</BODY>\n");
	fprintf(cgiOut,"</HTML>\n");

}
