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
    char *const av[]={"test1", "3", "5", "7", (char*)0};

    execvp("./test1", av);
    printf("execution(execv) fails...\n");
    exit(1);
}