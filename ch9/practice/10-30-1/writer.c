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

    fd=open("temp", O_RDONLY|O_CREAT, 0600);
    addr = mmap(NULL, 512, PROT_READ, MAP_SHARED, fd, 0);

    sleep(5);
    for(i=0;i<5;i++) {
        printf("%d\n", *(addr+i));
    }
    sleep(5);
    for(i=5;i<10;i++) {
        printf("%d\n", *(addr+i));
    }

    exit(0);
}