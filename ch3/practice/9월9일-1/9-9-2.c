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
    if (access("data1",F_OK) == 0){
        if (access("data1", R_OK | W_OK) == 0)
            printf("File exists: Read/write operations are permitted.\n");
        else
            printf("File exists: Read/write operations are not permitted.\n");
    }
    else
        printf("No such file or directory ...\n");

    return 0;
}
