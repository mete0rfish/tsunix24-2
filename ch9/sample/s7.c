#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>
#include <sys/mman.h>

int main() {
    int fd, i;
    char *addr;
    pid_t pid;

    fd = open("data7", O_RDWR);
    printf("%d\n", fd);

    addr = mmap(NULL, 10, PROT_WRITE, MAP_SHARED, fd, 0);
    printf("%p\n", addr);

    wait(0);
    exit(0);
}