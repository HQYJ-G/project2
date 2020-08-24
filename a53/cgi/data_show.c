#include"cgic.h"
#include"common.h"
#include"sem.h"

int cgiMain()
{
	key_t key;
	int shmid;
	int semid;
	sSensorType * data;
	
	if ((key = ftok("/project2",0x111)) == -1)
	{
		perror("ftok");
		return -1;
	}

	if ((shmid = shmget(key, sizeof(sSensorType), 0666)) == -1)
	{
		perror("shmget");
		return -1;
	}

	semid = semget(key, 1,0666);

	sem_p(semid);

	data = (sSensorType *)shmat(shmid, NULL, 0);

	cgiHeaderContentType("text/html");
	fprintf(cgiOut,"<HTML><HEAD>\n");
	fprintf(cgiOut,"<meta charset =\"utf-8\">\n");
	fprintf(cgiOut,"<TITLE>传感器数据</TITLE></HEAD>\n");
	fprintf(cgiOut,"<BODY><H1>传感器数据</H1>\n");

	fprintf(cgiOut,"<p>温度:%d.%d℃ </p>\n", data -> temperature[0],data -> temperature[1]);
	fprintf(cgiOut,"<p>湿度:%d.%d\%</p>\n", data -> humidity[0],data -> humidity[1]);
	fprintf(cgiOut,"<p>光照:%sLux</p>\n", data -> light);
//	fprintf(cgiOut,"<p>电压:%.2f</p>\n", data -> rp.voltage);
//	fprintf(cgiOut,"<p>陀螺仪:X:%4d Y:%4d Z:%4d</p>\n",data->mpu6050.gyrox,data->mpu6050.gyroy,data->mpu6050.gyroz);
//	fprintf(cgiOut,"<p>加速度:X:%4d Y:%4d Z:%4d</p>\n",data->mpu6050.accx,data->mpu6050.accy,data->mpu6050.accz);
	fprintf(cgiOut,"<a href = \"/index.html\"> back </a>\n");
	fprintf(cgiOut,"</BODY>\n");
	fprintf(cgiOut,"</HTML>\n");

	sem_v(semid);
	return 0;
}
