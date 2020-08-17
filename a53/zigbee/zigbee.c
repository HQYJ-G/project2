#include"zigbee.h"
#include<stdio.h>
#include"common.h"
#include"enum.h"
#include"sem.h"


void *ZigbeeWrite(void * arg)
{
	int fd;
	fd = (int)arg;
	
	key_t key;
	int qid;

	struct msgbuf msg;

	printf("%s start\n",__FUNCTION__);

	key = ftok("/project2",0x112);

	if(key == -1)
	{
		perror("key");
	}else
	{
		printf("%s ftok ok key:%d\n",__FUNCTION__,key);
	}

	qid = msgget(key, IPC_CREAT|0666);
	
	if(qid == -1)
	{
		perror("msgget");
	}else
	{
		printf("%s msgget ok qid:%d\n",__FUNCTION__,qid);
	}


	while(1)
	{
		if(msgrcv(qid, &msg, sizeof(MSG),0,0) == -1)
		{
			perror("msgrcv");
		}else
		{
			printf("%s msgrcv:%d-%d-%d\n",__FUNCTION__,msg.msg.cmd.type,msg.msg.cmd.control,msg.msg.cmd.status);
		}

		write(fd, &msg.msg, sizeof(MSG));

	}
}

void *ZigbeeRead(void * arg)
{
	int fd;
	fd = (int)arg;
	key_t key;
	int shmid;
	int semid;
	sSensorType *pSensor;
	MSG buf;

	key = ftok("/project2",0x111);

	shmid = shmget(key,sizeof(sSensorType),IPC_CREAT|0666);
	semid = semget(key, 1,IPC_CREAT|0666);

	init_sem(semid, 1);

	pSensor = (sSensorType *)shmat(shmid,NULL,0);

	while(1)
	{
		read(fd, buf, sizeof(sCmd));

		sem_p(semid);

		memcpy(pSensor->temperature,&buf.buf[0],2);
		pSensor->temperature[2] = '\0';

		memcpy(pSensor->humidity,&buf.buf[2],2);
		pSensor->humidity[2] = '\0';

		memcpy(pSensor->light,&buf.buf[4],1);
		pSensor->light[1]= '\0';

		sem_v(semid);
	}
	printf("ZigbeeRead\n");
}
