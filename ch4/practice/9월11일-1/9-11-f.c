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
    int data[10]={0}, fd, i;

    fd = open("test2", O_RDONLY);
    read(fd, data, sizeof(int) * 5);

    for(i=0;i<5;i++){
        printf("%d ", data[i]);
    }

    return 0;
}
