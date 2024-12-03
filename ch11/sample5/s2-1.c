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
    int fd, n1, n2, num1, num2, res1, res2;
    struct flock lock;

    fd = open("data1", O_RDWR|O_CREAT, 0600);

    lock.l_type=F_WRLCK;
    lock.l_whence=SEEK_CUR;
    lock.l_start=0;
    lock.l_len=sizeof(int);
    printf("%d\n", n1=fcntl(fd, F_SETLKW, &lock));

    sleep(1);

    if(n1==0) {
        lock.l_type=F_WRLCK;
        lock.l_whence=SEEK_SET;
        lock.l_start=sizeof(int);
        lock.l_len=sizeof(int);
        printf("%d\n", n2=fcntl(fd, F_SETLKW, &lock));

        if(n2 == 0) {
            read(fd, &num1, sizeof(int));
            read(fd, &num2, sizeof(int));
            res1=num1+num2;
            res2 =num2-num1;
            printf("%d %d %d %d\n", num1, num2, res1, res2);

            sleep(1);

            lseek(fd, 0, SEEK_SET);
            write(fd, &res1, sizeof(int));
            write(fd, &res2, sizeof(int));

            lock.l_type=F_UNLCK;
            lock.l_whence=SEEK_SET;
            lock.l_start=sizeof(int);
            lock.l_len=sizeof(int);
            fcntl(fd, F_SETLK, &lock);
        }

        lock.l_type=F_UNLCK;
        lock.l_whence=SEEK_SET;
        lock.l_start=0;
        lock.l_len=sizeof(int);
        fcntl(fd, F_SETLK, &lock);
    }

    return 0;
}