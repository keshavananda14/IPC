#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
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
	if((shmid = shmget(key,SHM_SIZE, IPC_CREAT | 0666)) < 0)
	{
		printf("Failed to create shared memory in client\n");
		return;
	}
	
	if((shm = shmat(shmid,NULL,0)) == (ShmData*)-1 )
	{
		printf("Failed to attach the shared memory\n");
		return;
	}
	
#if 1
	char buf[12] = {'\0'};
	int i = 0;
	while(1)
	{
		if(i>=12)
		{
			i = 0;
			printf("\n");
		}
			//printf("\n");
		printf("%c",shm->Shm[i].cSource[0]);
		i++;
		usleep(1000000);
	}
#else
	printf("### Name: %s , Size: %d  Status: %d ###\n",shm->Shm.cSource,shm->Shm.iSize,shm->Shm.iStatus);
	shm->Shm.iStatus = 1;	
#endif
	
	return;
}
