#include"sem.h"


/*函数名：init_sem
 *  功能：初始化sem
 *  参数：int sem_id semget的返回值 ，init_value 信号量初始值
 *  返回：成功返回0，失败返回-1
 */
int init_sem(int sem_id, int init_value)
{
	union semun sem_union;

	sem_union.val = init_value;
	if(semctl(sem_id, 0,SETVAL,sem_union) == -1)
	{
		perror("initialize semaphore");
		return -1;
	}

	return 0;
}

/*函数名：del_sem
 *  功能：删除sem
 *  参数：int sem_id semget的返回值
 *  返回：成功返回0，失败返回-1
 */
int del_sem (int sem_id)
{
	union semun sem_union;

	if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
	{
		perror("delete semaphore");
		return -1;
	}

	return 0;
}


/*函数名：sem_p
 *  功能：信号量P操作
 *  参数：int sem_id semget的返回值
 *  返回：成功返回0，失败返回-1
 */
int sem_p(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg =SEM_UNDO;

	if (semop(sem_id, &sem_b,1) == -1)
	{
		perror("P operation");
		return -1;
	}

	return 0;
}

/*函数名：sem_v
 *  功能：信号量v操作
 *  参数：int sem_id semget的返回值
 *  返回：成功返回0，失败返回-1
 */
int sem_v(int sem_id)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;
	if (semop(sem_id, &sem_b, 1) == -1)
	{
		perror("V operation");
		return -1;
	}

	return 0;
}
