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
    int res1 = link("test3.c", "test4.c");
    int res2 = link("test3.c", "A/B/C/test5.c");
    /*
    * A/B/C 가 없는 경우 -> -1 반환
    * A/B/C 가 있는 경우 -> test5.c 생성
    */

    printf("%d %d\n", res1, res2);
    return 0;
}
