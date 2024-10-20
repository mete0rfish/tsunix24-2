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

int main(void) {
    int loc[50], N = 0, i;
    DIR *dp;
    struct dirent *d;

    dp = opendir("./A");
    while(d = readdir(dp)) {
        loc[N++] = telldir(dp);
    }

    // N-1는 디렉토리의 끝을 가리킴
    for(i=N-2;i>=0;i--) {
        seekdir(dp, loc[i]);
        d = readdir(dp);
        printf("%d : %d : %s\n", telldir(dp), d->d_ino, d->d_name);
    }

    return 0;
}