/*
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/msg.h>
*/
#include"enum.h"
#include"cgic.h"
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

int cgiMain()
{
	char buf_1[16];
	char buf_2[16];
	
	key_t key;
	int qid;
	struct msgbuf msg;

	key = ftok("/project2", 0x112);

	qid = msgget(key, 0666);

	memset(&msg,0,sizeof(MSG));

	msg.msg.cmd.type = LED;
	msg.type = 1;

	cgiFormString("LED1", buf_1, 16);
	cgiFormString("LED2", buf_2, 16);

	msg.msg.cmd.control = LED1;

	if(!strncmp(buf_1, "ON", 2))
		msg.msg.cmd.status = ON;
	else
		msg.msg.cmd.status = OFF;

	msgsnd(qid, &msg,sizeof(MSG), 0);

	msg.msg.cmd.control = LED2;

	if(!strncmp(buf_2, "ON", 2))
		msg.msg.cmd.status = ON;
	else
		msg.msg.cmd.status = OFF;

	msgsnd(qid, &msg,sizeof(MSG), 0);

	cgiHeaderContentType("text/html");
	fprintf(cgiOut,"<HTML><HEAD>\n");
	fprintf(cgiOut,"<TITLE>led</TITLE></HEAD>\n");
	fprintf(cgiOut,"<BODY><H1>led</H1>\n");
	fprintf(cgiOut,"<p>LED1:%s</p>\n",buf_1);
	fprintf(cgiOut,"<p>LED2:%s</p>\n",buf_2);
	fprintf(cgiOut,"<p>qid %d</p>\n",qid);
	fprintf(cgiOut,"<a href = \"/led.html\"> back </a>\n");
	fprintf(cgiOut,"</BODY>\n");

	fprintf(cgiOut,"</HTML>\n");
	return 0;
}
