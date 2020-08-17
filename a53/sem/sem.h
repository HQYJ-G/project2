#ifndef __SEM_H__
#define __SEM_H__

#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/msg.h>

union semun
{
	int val;
	struct semid_id *buf;
	unsigned short *array;
};

int init_sem(int sem_id, int init_value);
int del_sem (int sem_id);
int sem_p(int sem_id);
int sem_v(int sem_id);

#endif
