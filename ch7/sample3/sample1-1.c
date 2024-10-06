#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>

void do_child(void) {
    int i;

    for(i=0;i<5;i++) {
        printf("child %ld running ...\n", getpid());
        sleep(1);
    }

    exit(0);
}

int main(void) {
    int i, status, N=3;
    pid_t pid;

    for(i=0;i<N;i++) {
        pid=fork();
        if(pid == 0) {
            do_child();
        }
    }

    exit(0);
}