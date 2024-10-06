#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>

void do_child(int N) {
    int i;

    for(i=0;i<5;i++) {
        printf("child %ld running ...\n", getpid());
        sleep(1);
    }

    exit(N);
}

int main(void) {
    int i, status, N=3;
    pid_t pid;

    for(i=0;i<N;i++) {
        pid=fork();
        if(pid == 0) {
            do_child(i);
        }
    }
    for(i=0;i<N;i++) {
        pid=wait(&status);
        if(WIFEXITED(status)) {
            printf("%ld ... %d\n", pid, WEXITSTATUS(status));
        }
    }

    exit(0);
}