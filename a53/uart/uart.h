#ifndef __UART_H__
#define __UART_H__

#include<stdio.h>
#include<string.h>
#include<termios.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int open_uart(char * port);
int close_uart(int fd);
int set_uart(int fd,int baud_rate,int data_bits,char parity,int stop_bits);
int uart_init();
#endif
