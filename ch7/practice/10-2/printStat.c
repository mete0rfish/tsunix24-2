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
    pid_t pid = getpid();
    for(i=0;i<5;i++) {
        sleep(1);
        printf("%ld %ld %ld\n" , pid, getpgrp(), getsid(pid));
    }
    exit(1);
    return 0;
}

