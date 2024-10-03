#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>

int main(void) {
    DIR *dp;
    struct dirent *d;

    dp=opendir(".");
    d=readdir(dp);
    while(d!=NULL) {
        printf("%ld : %s\n", d->d_ino, d->d_name);
        d=readdir(dp);
    }

    return 0;

}