#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include"zigbee.h"
#include"uart.h"
#include"sqlite.h"
#include"common.h"

/*
typedef struct
{
	char data[64];
	int argc;
}sLog;

void *SelectLog(void *arg)
{
	sDes *des = (sDes *)arg;
	key_t key;
	int shmid;
	int semid;
	sLog *psLog;
	
	key = ftok("/project2",0x120);
	
	if(key == -1)
	{
		perror("key");
	}else
	{
		printf("%s ftok ok key:%d\n",__FUNCTION__,key);
	}

	shmid = shmget(key,sizeof(psLog)*100+4,IPC_CREAT|0666);
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

	psLog = (sLog *)shmat(shmidm,NULL,0);

	while(1)
	{
		sem_p(semid);
			while(!strncmp(psLog,"OK",2));
			Select(des.db,"cmd","a");


		sem_v(semid);
	
	}

}
*/

int main(int argc, const char *argv[])
{
	pthread_t M0_Read;
	pthread_t M0_Write;
//	pthread_t Html_Log;

	int fd;
	sDes des;

	des.fd = uart_init();
	if (des.fd == -1)
	{
		printf("uart_init_failed\n");
		return -1;
	}

	des.db = open_sqlite("log");

	CreateTable(des.db,"cmd","ID INTEGER PRIMARY KEY AUTOINCREMENT,CMD TEXT,DATE TEXT");

	CreateTable(des.db,"env_data","ID INTEGER PRIMARY KEY AUTOINCREMENT,data TEXT,DATE TEXT");

	pthread_create(&M0_Read, NULL, ZigbeeRead,(void *)&des);
	pthread_create(&M0_Write, NULL, ZigbeeWrite,(void *)&des);
//	pthread_create(&Html_Log, NULL, SelectLog,(void *)&des);

	pthread_join(M0_Read,NULL);
	pthread_join(M0_Write,NULL);
//	pthread_join(Html_Log,NULL);

	close_sqlite(des.db);
	close_uart(des.fd);
	return 0;
}
