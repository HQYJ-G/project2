#include"../monitor_common.h"
#include"cgic.h"

int cgiMain()
{
	key_t key;
	int shmid;
	int semid;
	struct env_data * data;
	
	if ((key = ftok("/monitor_project",0x222)) == -1)
	{
		perror("ftok");
		exit(1);
	}

	if ((shmid = shmget(key, sizeof(struct env_data), 0666)) == -1)
	{
		perror("shmget");
		exit(1);
	}

	semid = semget(key, 1,0666);

	sem_p(semid);

	data = (struct env_data *)shmat(shmid, NULL, 0);

	cgiHeaderContentType("text/html");
	fprintf(cgiOut,"<HTML><HEAD>\n");
	fprintf(cgiOut,"<meta charset =\"utf-8\">\n");
	fprintf(cgiOut,"<TITLE>传感器数据</TITLE></HEAD>\n");
	fprintf(cgiOut,"<BODY><H1>传感器数据</H1>\n");

	fprintf(cgiOut,"<p>温度:%.2f</p>\n", data -> thtb.temperature);
	fprintf(cgiOut,"<p>湿度:%.2f</p>\n", data -> thtb.humidity);
	fprintf(cgiOut,"<p>电压:%.2f</p>\n", data -> rp.voltage);
	fprintf(cgiOut,"<p>陀螺仪:X:%4d Y:%4d Z:%4d</p>\n",data->mpu6050.gyrox,data->mpu6050.gyroy,data->mpu6050.gyroz);
	fprintf(cgiOut,"<p>加速度:X:%4d Y:%4d Z:%4d</p>\n",data->mpu6050.accx,data->mpu6050.accy,data->mpu6050.accz);
	fprintf(cgiOut,"<a href = \"/index.html\"> back </a>\n");
	fprintf(cgiOut,"</BODY>\n");
	fprintf(cgiOut,"</HTML>\n");

	sem_v(semid);
	return 0;
}
