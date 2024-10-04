#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>

int main(void){
    char ch='X';
    int i, fd;

    //1-(a)
    fd = open("data1", O_RDWR | O_CREAT, 777);
    for (i=0;i<10;i++){
        write(fd, &ch, 1);
    }

    // 1-(b)
    lseek(fd, 0, SEEK_SET);
    write(fd, "Y", 1);

    // 1-(c)
    lseek(fd, 0, SEEK_END);
    write(fd, "Y", 1);

    for (i=1;i<8;i+=2) {
        // 1-(d)-2
        lseek(fd, i, SEEK_SET);
        write(fd, "Z", 1);
    }

    // 1-(e)
    lseek(fd, 14, SEEK_SET);
    write(fd, "T", 1);

    // 1-(f)
    lseek(fd, -2, SEEK_END);
    write(fd, "S", 1);

    // 1-(g)
    lseek(fd, -2, SEEK_CUR);
    write(fd, "W", 1);
    return 0;
}