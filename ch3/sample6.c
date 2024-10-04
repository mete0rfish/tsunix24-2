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
    struct stat buf;

    // test6.c가 가르키는 A/B/C/test4.c의 정보
    stat("test6.c", &buf);
    printf("%o, %ld\n", buf.st_mode&0777, buf.st_size);
    printf("%s\n", ctime(&buf.st_mtime));

    // test6.c의 정보
    lstat("test6.c", &buf);
    printf("%o, %ld\n", buf.st_mode&0777, buf.st_size);
    printf("%s\n", ctime(&buf.st_mtime));

    return 0;
}
