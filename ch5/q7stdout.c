#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

	int cpid = fork();
	
	// parent
	if (cpid) {
		wait(NULL);
		printf("Parent after child finished!!\n");	
	}

	// child
	else {
		printf("Hello!\n");
		close(STDOUT_FILENO);
		printf("Will print work?\n");
	}
	return 0;

}
