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

void do_child(int fd) {
    int in;
    pid_t pid=getpid();
    struct flock lock;

    // F_RDLCK일 경우, 1로 계속 고정
    lock.l_type=F_WRLCK;
    lock.l_whence=SEEK_SET;
    lock.l_start=0;
    lock.l_len=sizeof(int);
    fcntl(fd, F_SETLKW, &lock);

    // lock 시, 포인터가 이동했기 때문에 처음으로 되돌림
    lseek(fd, 0, SEEK_SET);
    read(fd, &in, sizeof(int));
    printf("%ld reads %d ... \n", pid, in);
    sleep(5);

    in=in+10;
    lseek(fd, 0, SEEK_SET);
    write(fd, &in, sizeof(int));
    printf("%ld writes %d ... \n", pid, in);

    lock.l_type=F_UNLCK;
    lock.l_whence=SEEK_SET;
    lock.l_start=-sizeof(int);
    lock.l_len=sizeof(int);
    fcntl(fd, F_SETLK, &lock);

    exit(0);
}

int main(void){
    int i, in, fd;
    pid_t pid;

    fd=open("data1", O_RDWR|O_CREAT, 0600);
    scanf("%d", &in);
    write(fd, &in, sizeof(int));

    for (i=0; i<3; i++){
        pid=fork();
        if (pid==0)
            do_child(fd);
    }
    for (i=0; i<3; i++)
        wait(0);
    

    printf("%d\n", in);

    exit(0);
}