#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
int main(void)
{
	long int i;
	clock_t start, stop;
	double duration;
	double newduration;
	pid_t pid;
	pid_t sonpid;
	pid_t grandsonpid;
	pid_t bisnietopid;
	
	for (i=0; i<1; i++){
		pid = fork();
		start = clock();
		if (pid == 0) {
			if (i%2 == 0) {
				sonpid = fork();
				if (sonpid == 0){
					if(i%3 == 0){
						for (i=0; i<1000000; i++);
						wait(NULL);
						grandsonpid = fork();
						if (grandsonpid == 0){
							if (i%4 == 0){
								for (i=0; i<1000000; i++);
								wait(NULL);
								bisnietopid = fork();
								if ( bisnietopid == 0){
									for (i=0; i<1000000; i++);
										stop = clock();
									
								} 
							}
						
						} 				
					}			
				}
			
			} break;
		} else{
			duration = (double)(start - stop) / CLOCKS_PER_SEC;
			
		}
	} 
	double d1 = fabs(duration);
	
	printf("El numero de segundos en trabajar fue %f\n", d1);
	return 0;
}
