#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main (void) {
	pid_t child_pid;
	pid_t wait_result;
	child_pid = fork();
	int a =10;
	int status;
	if (child_pid == 0){
		printf(" Se esta ejecutando el hijo ");		
	}
	else {
		while (a <20) {
			printf( "value of: %d\n", a);
			a++;
		}							
	}
	return 0;
}
