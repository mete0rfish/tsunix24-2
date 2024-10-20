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
    int fd;

    fd = open("data1", O_RDWR);
    perror("open error : ");

    unlink("data1");
    perror("unlink error : ");

    return 0;
}
