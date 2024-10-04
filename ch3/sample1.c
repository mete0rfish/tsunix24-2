#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>
#include <c++/v1/ctime>

int main(void) {
    struct stat buf;

    stat("p1.c", &buf);
    printf("%o, %ld\n", buf.st_mode&0777, buf.st_size);
    printf("%s", ctime(&buf.st_mtime));

    return 0;
}
