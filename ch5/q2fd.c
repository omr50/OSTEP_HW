#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

void fileWriter(int fd, int arr[], size_t size) {
    write(fd, arr, size);
}

int main() {
    char arr[100000];
    int arr0[100000];
    for (int i = 0; i < 100000; i++) {
        arr[i] = 'a';
	arr0[i] = 'b';
    }

    // Specify the file permissions
    int fd = open("write.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    int cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Parent
    if (cpid) {
        printf("Parent file write\n");
        fileWriter(fd, arr, 100000);
        wait(NULL);
    }
    // Child
    else {
        printf("Child file write\n");
        fileWriter(fd, arr0, 100000);
        _exit(0); // Use _exit in child to avoid flushing shared buffers
    }

    close(fd);
    return 0;
}

