#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {

    int fd = open("./file.txt",  O_RDWR);
    int rc = fork();

    if(rc < 0) {
        fprintf(stderr, "fork failed \n");
        exit(1);
    }
    else if (rc == 0) {
        printf("Child process's file descriptor is %d \n", fd);
        const char* childMsg = "Written by child process";
        write(fd, childMsg, strlen(childMsg));
        close(fd);
    }
    else {
        printf("Parent process's file descriptor is %d \n", fd);
        const char* parentMsg = "Written by parent process";
        write(fd, parentMsg, strlen(parentMsg));
        close(fd);
    }
}
