#include"enum.h"
#include"cgic.h"
#include<sys/ipc.h>
#include<sys/types.h>
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

	msg.msg.cmd.type = BUZZER;
	msg.type = 1;


	cgiFormString("BUZZER", buf_6, 16);

	
	if(!strncmp(buf_6, "ON", 2))
		msg.msg.cmd.status = ON;
	else
		msg.msg.cmd.status = OFF;
	

	msgsnd(qid, &msg,sizeof(MSG), 0);

	cgiHeaderContentType("text/html");
	fprintf(cgiOut,"<HTML><HEAD>\n");
	fprintf(cgiOut,"<TITLE>buzzer</TITLE></HEAD>\n");
	fprintf(cgiOut,"<BODY><H1>buzzer</H1>\n");
	fprintf(cgiOut,"<p>BUZZER:%s</p>\n",buf_6);

	fprintf(cgiOut,"<p>qid %d</p>\n",qid);
	fprintf(cgiOut,"<a href = \"/buzzer.html\"> back </a>\n");
	fprintf(cgiOut,"</BODY>\n");

	fprintf(cgiOut,"</HTML>\n");
	return 0;
}
