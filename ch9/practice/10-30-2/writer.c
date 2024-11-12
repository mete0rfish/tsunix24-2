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

void catchsig(int signo);

int main() {
    char *addr;
    int fd1, fd2, i, n, len=0;
    pid_t *pid;
    static struct sigaction act;
    // signal handler 설정
    act.sa_handler = catchsig;

    fd1=open("data", O_RDWR | O_CREAT, 0600);
    fd2=open("temp", O_RDONLY | O_CREAT, 0600);

    pid=mmap(NULL, sizeof(pid_t), PROT_WRITE, MAP_SHARED, fd1, 0);
    addr=mmap(NULL, 512, PROT_READ, MAP_SHARED, fd2, 0);
    
    ftruncate(fd1, sizeof(pid_t));
    *pid = getpid();
    
    for (i=0; i<3; i++){
        pause();
        write(1, read+len, 512);
        write(1, "-------\n", 8);
        if (len>512)
            break;
    }
    exit(0);
}

void catchsig(int signo) {

}