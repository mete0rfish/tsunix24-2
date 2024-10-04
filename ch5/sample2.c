#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>

int list(const char *name, const struct stat *status, int type) {

    if(type == FTW_F) {
        printf("F % -30s\n", name);
    }
    else if(type == FTW_D) {
        printf("D % -30s\n", name);
    }
    else if(type == FTW_DNR) {
        printf("DNR % -30s\n", name);
    }
    else if(type == FTW_SL) {
        printf("SL % -30s\n", name);
    }
    else if(type == FTW_NS) {
        printf("NS % -30s\n", name);
    }
    return 0;
}

int main(void) {
    ftw(".", list, 1);
    
    return 0;
}
