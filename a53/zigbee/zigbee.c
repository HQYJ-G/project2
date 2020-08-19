#include"zigbee.h"
#include<stdio.h>
#include"common.h"
#include"enum.h"
#include"sem.h"

/*函数名：ZigbeeWrite
 * 	功能：通过串口向zigbee协调器写入数据
 * 	参数：
 *返回值：
 */
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
/*		
		if(msg.msg.cmd.status == ON)
		{
			write(fd, "on", 3);
		}else
		{
			write(fd, "off", 4);
		}
*/		
	}
}

/*函数名：ZigbeeRe
 * 	功能：通过串口向zigbee协调器读取数据
 * 	参数：
 *返回值：
 */
void *ZigbeeRead(void * arg)
{
	int fd;
	fd = (int)arg;
	key_t key;
	int shmid;
	int semid;
	sSensorType *pSensor;
	MSG buf;

	printf("%s start\n",__FUNCTION__);

	key = ftok("/project2",0x111);

	if(key == -1)
	{
		perror("key");
	}else
	{
		printf("%s ftok ok key:%d\n",__FUNCTION__,key);
	}

	shmid = shmget(key,sizeof(sSensorType),IPC_CREAT|0666);
	if(shmid == -1)
	{
		perror("shmget");
	}else
	{
		printf("%s shmget ok key:%d\n",__FUNCTION__,shmid);
	}

	semid = semget(key, 1,IPC_CREAT|0666);
	if(semid == -1)
	{
		perror("semget");
	}else
	{
		printf("%s semget ok key:%d\n",__FUNCTION__,semid);
	}

	init_sem(semid, 1);

	pSensor = (sSensorType *)shmat(shmid,NULL,0);

	while(1)
	{
		/*
		sem_p(semid);
			memcpy(pSensor->temperature,"aa",3);
			memcpy(pSensor->humidity,"aa",3);
			memcpy(pSensor->light,"aa",3);
		sem_v(semid);
		*/
		printf("wait read\n");		
		read(fd, &buf, sizeof(MSG));
		printf("%s msgrcv:%d-%d-%d\n",__FUNCTION__,buf.cmd.type,buf.cmd.control,buf.cmd.status);
	/*	
		char c[32];
		read(fd, c, 32);
		printf("%s %s %s\n",__FUNCTION__ ,c,c+4);
		sem_p(semid);
	*/
		memcpy(pSensor->temperature,&buf.buf[0],2);
		pSensor->temperature[2] = '\0';
		
		memcpy(pSensor->humidity,&buf.buf[2],2);
		pSensor->humidity[2] = '\0';

		memcpy(pSensor->light,&buf.buf[4],1);
		pSensor->light[1]= '\0';
		
//		printf("%s %s %s\n",pSensor->temperature,pSensor->humidity,pSensor->light);
		sem_v(semid);
	}
	printf("ZigbeeRead\n");
}
