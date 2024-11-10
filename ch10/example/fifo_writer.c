#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>
#include <signal.h>

int main() {
    int fd, j, nread;
    char buf[512];

    if((fd=open("fifo", O_WRONLY | O_NONBLOCK)) < 0) {
        printf("fifo open failed\n");
        exit(1);
    }

    for(j=0;j<3;j++) {
        nread=read(0, buf, 512);
        write(fd, buf, nread);
    }

    exit(0);
}