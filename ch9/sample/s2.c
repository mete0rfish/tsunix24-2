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

    fd = open("data2", O_RDWR);
    if(fork() == 0){
        addr =mmap(NULL, 50, PROT_READ|PROT_WRITE, MAP_SHARED, fd ,0);
        printf("%s\n", addr);
    }
    else {
        addr =mmap(NULL, 50, PROT_READ|PROT_WRITE, MAP_SHARED, fd ,0);
        for(i=0;i<5;i++) {
            *(addr+i) = *(addr+i) +1;
        }
        printf(".....\n%s\n", addr);
    }

    wait(0);
    exit(0);
}