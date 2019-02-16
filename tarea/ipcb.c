#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include <unistd.h>
#define BUF_SIZE 1024
#define SHM_KEY 0x1234

struct shmseg {
	int cnt;
	int complete;
	char buf[BUF_SIZE];
};
int main(int argc, char*argv[]){
	int f;
	f = fork ();
	if (f == 0){
		execl("ipcb", (char*)NULL);
	}
	else
	{
		execl("ipcb", (char*)NULL);
	}
	int shmid;
	struct shmseg *shmp;
	shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
	if (shmid == -1){
		perror("Shared memory");
		return 1;
	}
	shmp = shmat (shmid, NULL, 0);
	if (shmp == (void*)-1){
		perror("Shared memory attach");
		return 1;
	}
	while (shmp->complete != 1) {
		printf("conexion sucesfull");
		if (shmp->cnt == -1) {
			perror("read");
			return 1;
		}
		printf("Reading process: shared memory: read");
		sleep(3);
	}
	
	if (shmdt(shmp) == -1) {
		perror("shmdt");
		return 1;
	}
	printf("Reading Process: Complete\n");
	return 0;
}
