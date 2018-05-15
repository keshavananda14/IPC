#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>

#define SHM_SIZE 4194304

typedef struct
{
	char cSource[15];
	int iStatus;
	int iSize;
}ShmData1;

typedef struct
{
        ShmData1 Shm;
}ShmData;

int main()
{
	ShmData *shm;
	int shmid;
	key_t key;
	
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

	printf("### Name: %s , Size: %d  Status: %d ###\n",shm->Shm.cSource,shm->Shm.iSize,shm->Shm.iStatus);
	shm->Shm.iStatus = 1;	
	
	return;
}
