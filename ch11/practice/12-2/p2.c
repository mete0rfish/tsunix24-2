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
#include <sys/sem.h>

int main(void){
    int i, in, fd, turn, n;
    pid_t pid;
    struct flock lock;
    fd=open("turn1", O_RDWR|O_CREAT, 0600);

    // Read Lock 사용 시, 동시에 출력됨
    lock.l_type=F_WRLCK;
    lock.l_whence=SEEK_SET;
    lock.l_start=0;
    lock.l_len=sizeof(int);
    fcntl(fd, F_SETLKW, &lock);

    pid=getpid();

    for (i=0; i<5; i++){
        sleep(1);
        printf("%ld\n", pid);
    }

    // 동기화를 위한 locking 연산
    lock.l_type=F_UNLCK;
    lock.l_whence=SEEK_SET;
    lock.l_start=0;
    lock.l_len=sizeof(int);
    fcntl(fd, F_SETLK, &lock);

    exit(0);
}