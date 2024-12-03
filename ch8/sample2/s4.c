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
    printf("signal catch ... \n");
}

int main(void) {
    int i, n;
    static struct sigaction act;

    act.sa_handler=catchint;
    sigaction(SIGINT, &act, NULL);

    n=pause();
    for(i=0;i<5;i++)
        printf("%d...%d\n",i,n);

    exit(0);
}