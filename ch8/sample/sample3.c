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

void catchsig(int signo);

void do_child() {
    int i;
    static struct sigaction act;

    act.sa_handler=catchsig;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);

    for(i=0;i<5;i++) {
        printf("child is running ... %d\n", i);
        sleep(1);
    }
    exit(0);
}

int main(void) {
    int i, status;
    pid_t pid;

    pid=fork();
    if(pid == 0) {
        do_child();
    }
    
    sleep(2);
    kill(pid, SIGINT);
    sleep(1);
    kill(pid, SIGUSR1);
    sleep(1);
    kill(pid, SIGUSR2);
    sleep(1);

    wait(&status);
    printf("exit status=%d\n", WEXITSTATUS(status));
    exit(0);
}

void catchsig(int signo) {
    int i, pid;

    for(i=0;i<5;i++) {
        printf("handling sig=%d ... \n", signo);
        sleep(1);
    }
}