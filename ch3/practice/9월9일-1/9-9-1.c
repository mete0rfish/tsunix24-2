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

    stat("data1", &buf);
    printf("mode: %hu, link count: %d, size: %lld\n",
        buf.st_mode, buf.st_nlink, buf.st_size 
    );
}