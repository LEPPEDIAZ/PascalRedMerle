#include <stdio.h>
#include <time.h>

int main (void)
{
	long int x;
	clock_t start, stop;
	start = clock();
	double duration;
	for (x=0 ; x <1000000; x++);
	for (x=0; x<1000000; x++);
	for (x=0; x<1000000; x++);
	stop = clock();
	duration = (double) (stop - start) / CLOCKS_PER_SEC;
	printf("\nEl numero de segundos en trabajar fue %f\n", duration);
	return 0;
}
