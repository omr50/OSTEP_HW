#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

long getTime(struct timeval start, struct timeval end) {
	return (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
}

int main() {
	char buffer;
	int pipe1[2];
	int pipe2[2];
	pipe(pipe1);
	pipe(pipe2);
	int cpid = fork();
	struct timeval start, end;
	gettimeofday(&start, NULL);
	getpid();
	gettimeofday(&end, NULL);
    	printf("System call time = %ld microseconds\n", getTime(start, end));
	// parent
	if (cpid == 0) { // Child process
			 
    	close(pipe1[1]);
    	close(pipe2[0]);
	for (int i = 0; i < 10000; i++) {
    		read(pipe1[0], &buffer, 1); // Wait for parent's signal
    		write(pipe2[1], &buffer, 1); // Immediately signal back to parent
	}				     
    	close(pipe1[0]);
    	close(pipe2[1]);
    	exit(0);
	} else { // Parent process
		 
    	close(pipe1[0]);
    	close(pipe2[1]);
    	gettimeofday(&start, NULL); // Record start time
	for (int i = 0; i < 10000; i++) {				    
    		write(pipe1[1], &buffer, 1); // Signal to child
    		read(pipe2[0], &buffer, 1); // Wait for child's signal
	}
    	gettimeofday(&end, NULL); // Record end time
    	close(pipe1[1]);
    	close(pipe2[0]);

    	long context_switch_time = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
    	printf("Context switch time = %f microseconds\n", (double)context_switch_time / 10000.0);
	}
		
	return 0;

}
