#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>

#define SHM_SIZE 419430004

typedef struct 
{
	char cSource[2];
	int iStatus;
	int iSize;
}ShmData1;

typedef struct
{
	ShmData1 Shm[13];
}ShmData;

int main()
{
	ShmData *shm;
	key_t key;
	int shmid;

	key = 12345;
	if((shmid = shmget(key,SHM_SIZE,IPC_CREAT | 0666)) < 0)
	{
		printf("Failed to create shared emory\n");
		return;
	}

	if((shm = shmat(shmid,NULL,0)) == (ShmData*)-1)
	{
		printf("Failed to attach shared emory\n");
		return;
	}

#if 1
	char buf[12] = {"Keshavananda"};
	int i = 0;
	while(1)
	{
		if(i>=12)
		{
			i = 0;
			printf("\n");
		}
		memset(&shm->Shm[i],'\0',sizeof(shm->Shm[i]));
		sprintf(shm->Shm[i].cSource,"%c",buf[i]);
		printf("%c",shm->Shm[i].cSource[0]);
		i++;
		usleep(100000);
	}
#else
	sprintf(shm->Shm.cSource,"Keshavananda");
	shm->Shm.iSize = 1024;
	shm->Shm.iStatus = 0;
	printf("Shared data: %s %d %d \n",shm->Shm.cSource,shm->Shm.iSize,shm->Shm.iStatus);
	while(!shm->Shm.iStatus)
		sleep(5);
#endif
	shmctl(shmid, IPC_RMID, NULL);
	return;
}
