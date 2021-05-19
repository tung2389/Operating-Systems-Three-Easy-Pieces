#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {

    int rc = fork();
    // Delete file content
    int fd = open("./temp.txt",  O_RDWR | O_TRUNC);
    char * emptyMsg = "";
    write(fd, emptyMsg, strlen(emptyMsg));

    if(rc < 0) {
        fprintf(stderr, "fork failed \n");
        exit(1);
    }
    else if (rc == 0) {
        printf("hello\n");
        // The child will write to the temp file ONLY after it has already printed the "hello" message.
        int fd = open("./temp.txt",  O_RDWR);
        const char* childMsg = "Written by child process";
        write(fd, childMsg, strlen(childMsg));
    }
    else if(rc != 0) {
        char* childMsg[12];
        size_t maxLen = 12;
        while(1) {
            int fd = open("./temp.txt", O_RDONLY);
            int len = read(fd, childMsg, maxLen);
            close(fd);
            if(len > 1) {
                break;
            }
        }

        printf("goodbye\n");
    }
}
