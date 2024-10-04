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
    
    int res = symlink("A/B/C/test4.c", "test6.c");
    printf("%d\n", res);

    return 0;
}
