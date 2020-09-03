#ifndef __ENUM_H__
#define __ENUM_H__
typedef unsigned short uint_16;
typedef unsigned char uint8_t;
	//控制设备的类型
	enum{
		FAN = 0,//风扇
		BUZZER,//蜂鸣器
		VR,		//电位器
		HUMITURE,//温湿度
		LED,	 //led灯
		RFID,	 //RFID
		DISPLAY,  //数码管
	};
	//具体哪个设备
	enum{
		LED1 = 0,//led1
		LED2,	 //led2
		TEM,	//温度
		HUM,	//湿度
		FANI,	//风扇
		FANII,
		FANIII,
		FANIV
	};
	//状态
	 enum{
		OFF = 0,//关
		ON		//开
	};
	typedef struct{
		uint_16 type:4;//0-3位
		uint_16 control:4;//4-7位
		uint_16 status:1;//8位
		//剩余9-15位留着以后扩展
	}sCmd;
	
	//命令字的封装-->用了16位的short的数据类型
/*命令字解析--16位
0-3位：			4-7位			8位： 9-15位留着以后扩展：
0000:风扇		0000:LED1		0:关
0001:蜂鸣器		0001:LED2		1:开
0010:电位器		0010:温度 
0011:温度采集器	0011:湿度
0100:led模拟		1000:风扇I级
0101:RFID		0101:风扇II级
0110:数码管
*/
	
	typedef struct {
		sCmd cmd;//解析操作的命令
		uint8_t buf[8];//传输的数据，如温湿度信息，光照信息等,温度1.2 湿度3.4 亮度5
					  //上传温湿度数据，下发温湿度上下限(整数表示上下限)
		
	}MSG;

struct msgbuf
{
	long type;
	MSG msg;
};
/*
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
};*/
#endif
