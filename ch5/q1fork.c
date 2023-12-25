#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int x = 100;

	int cpid = fork();
	
	// parent
	if (cpid) {
		printf("x = %d in child\n", x);
		// change x
		x = 200;
		printf("x changed in parent to %d\n", x);	
		// wait for child to finish to see if 
		// the change of x in child affects parent
		wait(NULL);
		printf("Did x change: %d\n", x);
	}

	else {
		printf("x = %d in parent\n", x);	
		x = 300;
		printf("x changed in child to %d\n", x);
	}
	return 0;

}
