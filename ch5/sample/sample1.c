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
    if(type == FTW_NS) {
        return 0;
    }
    if(type == FTW_F) {
        printf("% - 30s\t0%3o\n", name, status->st_mode&0777);
    }
    else {
        printf("% - 30s*\t0%3o\n", name, status->st_mode&0777);
    }
    return 0;
}

int main(void) {
    ftw(".", list, 1);
    
    return 0;
}
