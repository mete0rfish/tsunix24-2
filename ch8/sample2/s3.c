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

void catchint(int signo) {
    printf("DO NOT INTERRUPT ... \n");
}

int main(void) {
    int i, j, num[10], sum=0;
    sigset_t mask;
    static struct sigaction act;

    act.sa_handler=catchint;
    sigaction(SIGINT, &act, NULL);

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    for(i=0;i<5;i++){
        sigprocmask(SIG_SETMASK, &mask, NULL);
        scanf("%d", &num[i]);
        sigprocmask(SIG_UNBLOCK, &mask, NULL);
        sum += num[i];
        for(j=0;j<=i;j++){
            printf("... %d\n", num[j]);
            sleep(1);
        }
    }

    exit(0);
}