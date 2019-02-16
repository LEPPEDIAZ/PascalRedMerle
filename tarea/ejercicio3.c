#include <stdio.h>
#include <time.h>

int main (void)
{
	long int x;
	clock_t start, stop;
	start = clock();
	double duration;
	for (x=0 ; x <1000000; x++){
		printf("\n primer for", x);
		
	}
	for (x=0; x<1000000; x++){
		printf("\nsegundo for", x);
		
	}
	for (x=0; x<1000000; x++){
		printf("\ntercer for", x);
		
	}
	stop = clock();
	duration = (double) (stop - start) / CLOCKS_PER_SEC;
	printf("\nEl numero de segundos en trabajar fue %f\n", duration);
	return 0;
}
