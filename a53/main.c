#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include"zigbee.h"
#include"uart.h"


int main(int argc, const char *argv[])
{
	pthread_t M0_Read;
	pthread_t M0_Write;
	int fd;

	fd = uart_init();

	pthread_create(&M0_Read, NULL, ZigbeeRead,(void *)fd);
	pthread_create(&M0_Write, NULL, ZigbeeWrite,(void *)fd);

	pthread_join(M0_Read,NULL);
	pthread_join(M0_Write,NULL);
	return 0;
}
