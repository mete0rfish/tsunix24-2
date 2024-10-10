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

void catchint(int signo);

int main(void) {
    int i, status;
    pid_t pid;
    static struct sigaction act;

    act.sa_handler = catchint;
    sigaction(SIGINT, &act, NULL);

    pid=fork();
    if(pid == 0) {
        for(i=0;i<15;i++) {
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

void catchint(int signo) {
    printf("\n CATCHINT: signo=%d\n", signo);
}