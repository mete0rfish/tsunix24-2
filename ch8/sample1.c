#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>
#include <signal.h>

int main(void) {
    int i, status;
    pid_t pid;

    pid=fork();
    if(pid == 0) {
        for(i=0;i<100;i++) {
            printf("... child ... \n");
            sleep(1);
        }
        exit(0);
    }
    else {
        sleep(5);
        kill(pid, SIGINT);
    }
    wait(&status);
    if(WIFEXITED(status)) {
        printf("exits ... %d\n", WEXITSTATUS(status));
    }
    else if(WIFSIGNALED(status)) {
        printf("terminated ... %d\n", WTERMSIG(status));
    }

    exit(0);
}