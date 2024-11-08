#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>

int main(int argc, char **argv) {
    int i;
    for(i=0;i<5;i++) {
        sleep(1);
        printf("%s\n" , argv[1]);
    }
    exit(0);
    return 0;
}

