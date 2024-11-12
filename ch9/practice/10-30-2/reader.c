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
    char *addr;
    int fd1, fd2, i, n, len=0;
    pid_t *pid;
    
    fd1=open("data", O_RDWR);
    fd2=open("temp", O_RDWR);
    
    // writer에서 자신의 pid 입력
    pid=mmap(NULL, sizeof(pid_t), PROT_WRITE, MAP_SHARED, fd1, 0);
    // 
    addr=mmap(NULL, 512, PROT_WRITE | PROT_READ, MAP_SHARED, fd2, 0);
    
    ftruncate(fd1, sizeof(pid_t));
    ftruncate(fd1, 512);

    while (*pid==0);
    printf("writer id = %ld\n", *pid);

    for (i=0; i<3; i++){
        // read로 입력받은 내용을
        n = read(0, addr+len, 512-len);
        len+=n;

        if (len>=512)
            break;
        // writer에게 signal 보내기
        kill(*pid, SIGUSR1);
    }
    exit(0);
}