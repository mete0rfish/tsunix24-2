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


    pid=fork();
    if(pid == 0) {
        do_child(25);
    }

    while(1) {
        n=waitpid(pid, &status, 0);
        if(n>0) {
            if(WIFEXITED(status)) {
                printf("%ld ... %d\n", n, WEXITSTATUS(status));
            }
        }
        else if(n==0) {
            printf("waiting...\n");
        }
        else {
            break;
        }
        sleep(1);
    }

    exit(0);
}