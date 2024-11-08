#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>

int main(int argc, char **argv) {
    int i, fd;
    char data[50];
    fd = open("data", O_RDONLY);

    for(i=0;i<5;i++) {
        sleep(1);
        read(fd, data, 50);
        printf("%s\n", data);
        lseek(fd ,0, SEEK_SET);
    }

    close(fd);
    exit(2);
    return 0;
}

