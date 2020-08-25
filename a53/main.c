#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include"zigbee.h"
#include"uart.h"
#include"sqlite.h"
#include"common.h"


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
