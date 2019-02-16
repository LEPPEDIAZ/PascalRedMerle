#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main (void) {
	pid_t child_pid;
	pid_t wait_result;
	child_pid = fork();
	int a =10;
	int status;
	int array[40000];
	int count = 0;
	int i;
	
	if (child_pid == 0){
		for (i=1; i<=4000000000; i++){
			printf("%d\n",i);
		}
			
	}
	else {
		while (a <20) {
			printf( "value of: %d\n", a);
			a++;
		}							
	}
	return 0;
}
