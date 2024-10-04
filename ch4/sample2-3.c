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
    char ch1[30], ch2[15]="error message\n";
    int n;

    n=read(0, ch1, 30);
    write(1, ch1, n);
    write(2, ch2, 15);

    return 0;
}
