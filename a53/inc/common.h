#ifndef __MAIN_H__
#define __MAIN_H__

#include "sqlite.h"


struct EnvMsg
{
	char head[3];//标识位st:
	char type;//数据类型
	char snum;//仓库编号
	unsigned char temp[2];//温度
	unsigned char hum[2];//湿度
	char x; //三轴信息
	char y; 
	char z; 
	int lux;//光照
	int bet;//电池电量
	int adc; //电位器信息
};

typedef struct
{
	sqlite3 *db;
	int fd;
}sDes;
#endif
