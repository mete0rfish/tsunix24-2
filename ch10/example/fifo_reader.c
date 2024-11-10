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
    int fd, n;
    char buf[512];

    mkfifo("fifo", 0600);

    fd=open("fifo", O_RDONLY);

    for(;;) {
        n = read(fd, buf, 512);
        write(1, buf, n);
        if(n == 0) {
            printf("...\n");
        }
    }
}