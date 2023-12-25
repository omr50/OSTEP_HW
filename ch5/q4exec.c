#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

	int cpid = fork();
	
	// parent
	if (cpid) {
		wait(NULL);
		printf("Parent after child finishes exec ls\n");
	}

	else {
		printf("Child will exec ls!\n");
		execl("/bin/ls", "ls", "-l", (char *) NULL);
	}
	return 0;

}
