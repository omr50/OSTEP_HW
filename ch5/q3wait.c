#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

	int cpid = fork();
	
	// parent
	if (cpid) {
		wait(NULL);
		printf("Good Bye!\n");	
	}

	else {
		printf("Hello!\n");
	}
	return 0;

}
