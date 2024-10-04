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
    int data=35, fd, i;

    fd = open("test2", O_WRONLY | O_CREAT, 0640);
    for(i=0;i<10;i++){
        write(fd, &data, sizeof(data));
    }

    return 0;
}
