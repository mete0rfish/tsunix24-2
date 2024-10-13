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

void catchusr(int signo);

void do_child(int i){
    int pid;
    static struct sigaction act;

    act.sa_handler=catchusr;
    sigaction(SIGUSR1, &act, NULL);

    printf("%d-th child is created...\n", i);
    pause();

    exit(i);
}
int main(void) {
    int i, cid, status;
    pid_t pid[3];
    for (i=0;i<3;i++){
        pid[i]=fork();
        if (pid[i]==0) {
            do_child(i);
        }
    }

    for(i=0;i<3;i++) {
        kill(pid[i], SIGUSR1);
        sleep(1);
    }

    for (i=0;i<3;i++){
        cid=wait(&status);
        printf("child id=%d, exit status=%d\n", cid, WEXITSTATUS(status));
    }
    exit(0);
}

void catchusr(int signo) {
    int i;
    pid_t pid = getpid();
    for(i=0;i<3;i++) {
        printf("pid: %d\n", pid);
        sleep(1);
    }
}