#include<stdio.h>
#include<string.h>
#include<termios.h>
#include"uart.h"

int open_uart(char * port)
{
	int fd;
	fd = open(port, O_RDWR|O_NOCTTY|O_NDELAY);

	if (fd == -1)
	{
		perror("open_uart");
		return -1;
	}

	if (fcntl(fd, F_SETFL,0) < 0)
	{
		printf("fcntl failed\n");
		return -1;
	}

	if(!isatty(STDIN_FILENO))
	{
		printf("isatty failed\n");
		return -1;
	}

	printf("open uart succeed\n");
	return fd;
}

int close_uart(int fd)
{
	close(fd);
}

int set_uart(int fd, int baud_rate, int data_bits, char parity, int stop_bits)
{
	struct termios new_cfg, old_cfg;
	int speed;

	if (tcgetattr(fd, &old_cfg))
	{
		perror("tcgettattr");
		return -1;
	}

	new_cfg = old_cfg;

	cfmakeraw(&new_cfg);
	new_cfg.c_cflag &= ~CSIZE;

	switch(baud_rate)
	{
		case 2400:{
				  	speed = B2400;
					break;
				  }
		case 4800:{
				  	speed = B4800;
					break;
				  }
		case 9600:{
				  	speed = B9600;
					break;
				  }
		case 19200:{
				   	speed = B19200;
				   	break;
				   }
		case 38400:{
				   	speed = B38400;
					break;
				   }
		case 115200:{
					speed = B115200;
					break;
					}
		default:{
					printf("invalid baud rate\n");
					return -1;
				}
	}
	
	cfsetispeed(&new_cfg, speed);
	cfsetospeed(&new_cfg, speed);

	switch(data_bits)
	{
		case 7:{
			   		new_cfg.c_cflag |=CS7;
			   		break;
			   }
		case 8:{
			   		new_cfg.c_cflag |=CS8;
					break;
			   }
		default:{
					printf("invalid data bits\n");
				}
	}

	switch (parity)
	{
		case 'n':
		case 'N':{
				 	new_cfg.c_cflag &= ~PARENB;
					new_cfg.c_iflag &= INPCK;
				 }
	}

	switch (stop_bits)
	{
		case 1:{
			   		new_cfg.c_cflag &= ~CSTOPB;
					break;
			   }
	}

	new_cfg.c_cc[VTIME] = 0;
	new_cfg.c_cc[VMIN] = 1;
	tcflush(fd, TCIFLUSH);

	if ((tcsetattr(fd, TCSANOW, &new_cfg)))
	{
		perror("tcsetattr");
		return -1;
	}

	printf("set uart succeed\n");
	return 0;
}

int uart_init(void)
{
	int fd;

	fd = open_uart("/dev/ttyUSB0");

	set_uart(fd, 115200, 8, 'n', 1);

	return fd;
}
