#include <stdio.h>
#include <unistd.h>

int main() {
	fork();
	fork();
	fork();
	fork();
	printf("Pascal Red Merle\n");
	return 0;
}
