#include"zigbee.h"
#include<stdio.h>
#include"common.h"
#include"enum.h"
#include"sem.h"
#include"sqlite.h"
#include<time.h>


int qid;
int shmid;
int semid;
struct EnvMsg *pEnvMsg;

/*函数名：ZigbeeWrite
 * 	功能：通过串口向zigbee协调器写入数据
 * 	参数：
 *返回值：
 */
void *ZigbeeWrite(void * arg)
{
	int fd;
	sDes *des = (sDes *)arg;
	fd = ((sDes *)arg)->fd;
	key_t key;
	struct msgbuf msg;
	char sqlval[128];
	time_t t;


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
		memset(&msg,0,sizeof(MSG));
		if(msgrcv(qid, &msg, sizeof(MSG),0,0) == -1)
		{
			perror("msgrcv");
		}else
		{
			time(&t);
			printf("%s msgrcv:%d-%d-%d\n",__FUNCTION__,msg.msg.cmd.type,msg.msg.cmd.control,msg.msg.cmd.status);
			sprintf(sqlval,"\"%d_%d_%d\",\"%s\"",msg.msg.cmd.type,msg.msg.cmd.control,msg.msg.cmd.status,ctime(&t));

		}
		Insert(des->db,"cmd","CMD,DATE",sqlval);

		write(fd, &msg.msg, sizeof(MSG));
	/*发送字符测试	
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
	sDes *des = (sDes *)arg;
	fd = ((sDes *)arg)->fd;

	key_t key;
	char sqlval[128];
	int flag = 0;
	time_t t;

	printf("%s start\n",__FUNCTION__);

	key = ftok("/project2",0x111);

	if(key == -1)
	{
		perror("key");
	}else
	{
		printf("%s ftok ok key:%d\n",__FUNCTION__,key);
	}

	shmid = shmget(key,sizeof(struct EnvMsg),IPC_CREAT|0666);
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

	pEnvMsg = (struct EnvMsg *)shmat(shmid,NULL,0);

	while(1)
	{
		/*测试用虚拟数据
		sem_p(semid);
			memcpy(pSensor->temperature,"aa",3);
			memcpy(pSensor->humidity,"aa",3);
			memcpy(pSensor->light,"aa",3);
		sem_v(semid);
		*/
		
		printf("wait read\n");	

		sem_p(semid);
		read(fd, pEnvMsg, sizeof(struct EnvMsg));
		sem_v(semid);
		if(10 == flag++)
		{
			time(&t);

			sprintf(sqlval,"\"%d.%d\",\"%d.%d\",\"%s\"",pEnvMsg->temp[0],pEnvMsg->temp[1],pEnvMsg->hum[0],pEnvMsg->hum[1],ctime(&t));
			Insert(des->db,"env_data","TEMP,HUM,DATE",sqlval);
			flag = 0;
		}

	}

	shmdt(pEnvMsg);
}
