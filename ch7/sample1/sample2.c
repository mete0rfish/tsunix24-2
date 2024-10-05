#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>

int main(void) {
    pid_t pid;
    
    printf("pid=%ld ... ppid:%ld\n", getpid(), getppid());

    pid = fork();
    if(pid == 0) {
        printf("pid=%ld ... ppid:%ld\n", getpid(), getppid());
        sleep(5);
        printf("pid=%ld ... ppid:%ld\n", getpid(), getppid());
        return 0;
    }

    sleep(1);
    return 0;
}