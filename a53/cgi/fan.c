#include"enum.h"
#include"cgic.h"
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

int cgiMain()
{

	char buf_6[16];

	
	key_t key;
	int qid;
	struct msgbuf msg;

	key = ftok("/project2", 0x112);

	qid = msgget(key, 0666);

	memset(&msg,0,sizeof(struct msgbuf));

	msg.msg.cmd.type = FAN;
	msg.type = 1;

	cgiFormString("FAN", buf_6, 16);

	
	if(!strncmp(buf_6, "HIGH", 4))
	{
		msg.msg.cmd.control = FANI;
		msg.msg.cmd.status = ON;
	}
	else if(!strncmp(buf_6,"LOW",3))
	{
		msg.msg.cmd.control = FANII;
		msg.msg.cmd.status = ON;
	}else
	{
		msg.msg.cmd.status = OFF;
	}

	msgsnd(qid, &msg,sizeof(MSG), 0);

	cgiHeaderContentType("text/html");
	fprintf(cgiOut,"<HTML><HEAD>\n");
	fprintf(cgiOut,"<TITLE>fan</TITLE></HEAD>\n");
	fprintf(cgiOut,"<BODY><H1>fan</H1>\n");
	fprintf(cgiOut,"<p>FAN:%s</p>\n",buf_6);
	fprintf(cgiOut,"<p>qid %d</p>\n",qid);
	fprintf(cgiOut,"<a href = \"/fan.html\"> back </a>\n");
	fprintf(cgiOut,"</BODY>\n");

	fprintf(cgiOut,"</HTML>\n");
	return 0;
}
