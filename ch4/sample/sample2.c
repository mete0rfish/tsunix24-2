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
    char ch[100];
    int fd, n;

    fd = open("data2", O_RDONLY);
    n = read(fd, ch, 99);
    ch[n]='\0';
    printf("fd=%d, n=%d, ch=%s\n", fd, n, ch);
    /*
    * data2가 공백일 경우, n = 0
    */

    return 0;
}
