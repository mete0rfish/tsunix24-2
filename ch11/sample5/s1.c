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
#include <sys/shm.h>
#include <sys/lock.h>

int main(int argc, char** argv) {
    int fd, i, num;
    struct flock lock;

    fd=open("data1", O_RDWR|O_CREAT, 0600);

    for(i=0;i<10;i++) {
        lock.l_type=F_WRLCK;
        lock.l_whence=SEEK_CUR;
        lock.l_start=0;
        lock.l_len = sizeof(int);
        fcntl(fd, F_SETLKW, &lock);

        read(fd, &num, sizeof(int));
        num=num+10;
        sleep(1);
        lseek(fd, -sizeof(int), SEEK_CUR);
        write(fd, &num, sizeof(int));

        lock.l_type=F_UNLCK;
        lock.l_whence=SEEK_CUR;
        lock.l_start=-sizeof(int);
        lock.l_len = sizeof(int);
        fcntl(fd, F_SETLK, &lock);
        printf("%d\n", num);
    }

    return 0;
}