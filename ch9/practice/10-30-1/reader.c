#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<ftw.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/mman.h>

int main() {
    int fd, i;
    int *addr;

    fd=open("temp", O_RDWR|O_CREAT, 0600);
    addr = mmap(NULL, 512, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

    ftruncate(fd, 512);

    for(i=0;i<10;i++) {
        scanf("%d", addr+i);
    }

    exit(0);
}