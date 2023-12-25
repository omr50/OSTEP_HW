#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

	int pipe1[2];
	pipe(pipe1);

	int cpid1 = fork();
	// create pipe
	int cpid2;
	printf("MY PID is %d\n", getpid());

	// parent
	if (cpid1) {
		printf("This is the parent\n");
		cpid2 = fork();
		// child 2
        	if (cpid2 == 0) {
                	dup2(pipe1[1], STDOUT_FILENO);
                	close(pipe1[0]);
                	printf("HelloWorld\n");
                	printf("Goodbye!\n");
                	printf("ImBACK\n");
        	}
		wait(NULL);
		wait(NULL);
		printf("Both children are finished\n");	
	}

	// if child 1, then its write i
	else if (cpid1 == 0) {
		dup2(pipe1[0], STDIN_FILENO);
		close(pipe1[1]);
		char a[13];
		for (int i = 0; i < 3; i++) {
			scanf("%s", a); 
			printf("child 1 scanned in %s\n", a);
		}
	}
		
	return 0;

}
