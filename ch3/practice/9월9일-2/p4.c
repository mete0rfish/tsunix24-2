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
    char name[50];
    scanf("%s", name);
    struct stat buf;

    lstat(name, &buf);
    printf(
        "acess permission : %d,size: %d, name: %s\n",
        buf.st_mode, buf.st_size, name
    );

    stat(name, &buf);
    printf(
        "acess permission : %d,size: %d, name: %s\n",
        buf.st_mode, buf.st_size, name
    );


    return 0;
}
