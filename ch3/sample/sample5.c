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
    char ch[100]={0};

    readlink("test6.c", ch, 100);
    printf("%s\n", ch);
    
    return 0;
}
