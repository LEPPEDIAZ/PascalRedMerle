#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<wait.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<errno.h>
#define BUF_SIZE 1024
#define SHM_KEY 0x1234

struct shmseg {
	int cnt;
	int complete;
	char buf[BUF_SIZE];
};

int fill_buffer(char*bufptr, int size);
int main(int argc, char*argv[])
{
	int shmid, numtimes;
	struct shmseg *shmp;
	char *bufptr;
	int spaceavailable;
	shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0644|IPC_CREAT);
	if (shmid == -1){
		perror("Shared memory");
		return 1;
	}
	shmp = shmat(shmid, NULL, 0);
	if (shmp == (void*)-1){
		perror("Shared memory attach");
		return 1;
	}
	bufptr = shmp->buf;
	spaceavailable = BUF_SIZE;
	for (numtimes = 0; numtimes <5; numtimes ++){
		shmp->cnt = fill_buffer(bufptr, spaceavailable);
		shmp->complete = 0;
		printf("Writing Process: Shared Memory: Wrote %d bytes\n", shmp->cnt);
		bufptr = shmp->buf;
		spaceavailable = BUF_SIZE;
		sleep(3);
	}
	printf("Writing Process: Wrote %d times\n", numtimes);
	shmp->complete =1;
	if (shmdt(shmp) == -1){
		perror("shmdt");
		return 1;
	}
	if (shmctl(shmid, IPC_RMID, 0) == -1){
		perror("shmctl");
		return 1;
	}
	printf("Writing Process: Complete\n");
        pid_t pid;
        int r;
        char buf[1024];
        char cp[50];
        char ans;
        int readpipe[2];
        int writepipe[2];
        long int a;
        int b;
        a=pipe(readpipe);
        b=pipe(writepipe);

        if (a == -1) { perror("pipe"); exit(EXIT_FAILURE); }
        if (b == -1) { perror("pipe"); exit(EXIT_FAILURE); }
       
        scanf("%[^\n]%*c",&ans);
        fflush(stdin);
        pid=fork();
        if(pid==-1)
        {
                printf("pid:main");
                exit(1);
        }
        while(1)
        {
                if(pid==0)
                { 
             
                         if(ans=='n')
                        {
                             
                                kill(pid,SIGKILL);
                        }

                        close(readpipe[1]);
                        close(writepipe[0]);
                        if(read(readpipe[0],buf,sizeof(buf)) < 0)
                        {
                            break;
                        }
                        printf("\nCreated new shared mem obj: %s\n",buf);
                        printf("\n(child)a: \t");
                        fflush(stdin);
                        fgets(cp, 50, stdin);
                        printf("\n(Parent)b: %s",cp);
                        if(/*!strncmp("Q",cp,1) || */write(writepipe[1],cp,strlen(cp)+1) < 0)
                        {
                            break;
                        }
                        

                }
                else
                {
                        close(readpipe[0]);
                        close(writepipe[1]);
                        printf("\n(Parent)b:  \t");
                        fgets(cp, 50, stdin);
                        printf("\nshared memory has: %s",cp);
                        if(/*!strncmp("Q",cp,1) ||*/ write(readpipe[1],cp,strlen(cp)+1) < 0)
                        {
                            break;
                        }        

                        if(read(writepipe[0],buf,sizeof(buf)) < 0)
                        {
                            break;
                        }
                        printf("\n (parent)a: %s\n",buf);
                     
                        fflush(stdin);
                        scanf(" %[^\n]%*c",&ans);
                        if(ans=='n')
                        {
                                kill(pid,SIGKILL);
                        }
                }


        }
        close(readpipe[1]);
        close(writepipe[0]);
        close(readpipe[0]);
        close(writepipe[1]);
        return 0;
}
int fill_buffer(char * bufptr, int size){
	static char ch = 'A';
	int filled_count;

	memset(bufptr, ch, size -1);
	bufptr[size-1]='\0';
	if (ch > 122)
	ch = 65;
	if ((ch>= 65) && (ch <= 122)) {
		if ((ch >= 91) && (ch <= 96)){
			ch = 65;
		}
	}
	filled_count = strlen(bufptr);
	ch++;
	return filled_count;
}
