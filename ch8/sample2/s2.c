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

void catchalarm(int signo) {
    printf("\nCATCHALARM:signo=%d\n", signo);
    alarm(3);
}

int main(void) {
    int i,n;
    static struct sigaction act;

    act.sa_handler=catchalarm;
    sigaction(SIGALRM, &act, NULL);

    n = alarm(10);
    printf("알람설정: %d\n", n);

    for(i=0;i<10;i++) {
        printf("... child ... \n");
        if(i==1) {
            n=alarm(3);
            printf("알람 재설정: %d\n", n);
        }
        sleep(1);
    }

    exit(0);
}