#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>

int main(int argc, char** argv) {
    int i, N;
    pid_t pid;
    
    N=atoi(argv[1]);

    printf("pid=%ld ... ppid:%ld\n", getpid(), getppid());

    for(i=0;i<N;i++){
        pid = fork();
        if(pid == 0) {
            printf("%d: pid=%ld ... ppid=%ld\n", i, getpid(), getppid());            
        }
    }

    for(i=0;i<N;i++) {
        if(pid >0) {
            wait(0);
        }
    }

    return 0;
}
