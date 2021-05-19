#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    int x = 100;
    int rc = fork();

    if(rc < 0) {
        fprintf(stderr, "fork failed \n");
        exit(1);
    }
    else if (rc == 0) {
        printf("x value in child process is %d \n", x);
        x = 200;
        printf("Now x value in child process is %d \n", x);
    }
    else {
        x = 300;
        printf("Now x value in parent process is %d \n", x);
    }
}
