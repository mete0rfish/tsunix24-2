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
    int i, status, n;
    pid_t pid;

    for(i=0;i<3;i++) {
        pid=fork();
        if(pid == 0) {
            do_child(i);
        }
    }

    n=waitpid(pid, &status, 0);
    if(WIFEXITED(status)) {
        printf("%ld ... %d\n", n, WEXITSTATUS(status));
    }

    while(1) {
        n=waitpid(-1, &status, 0);
        if(n == -1) {
            break;
        }
        if(WIFEXITED(status)) {
            printf("%ld ... %d\n", n, WEXITSTATUS(status));
        }
    }

    exit(0);
}