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
    int *addr;
    pid_t pid;

    fd = open("data3", O_RDWR|O_CREAT, 0600);
    if(fork() == 0){
        addr =mmap(NULL, 50, PROT_READ|PROT_WRITE, MAP_SHARED, fd ,0);
        for(i=0;i<5;i++)
            printf("%d\n", *(addr+i));
    }
    else {
        addr =mmap(NULL, 50, PROT_READ|PROT_WRITE, MAP_SHARED, fd ,0);
        ftruncate(fd, sizeof(int) * 5);
        for(i=0;i<5;i++)
            *(addr+i) = i;
    }

    wait(0);
    exit(0);
}