#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>

int main(void) {
    char ch ='X';
    int fd, i;

    fd = open("test1",O_WRONLY | O_CREAT, 0600);
    for(i=0;i<10;i++) {
        write(fd, &ch, sizeof(ch));
    }

    return 0;
}
