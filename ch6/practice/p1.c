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
    if(type == FTW_D || type == FTW_DNR) {
        printf("%s : %lld\n", name, status->st_size);
    }
    else if(type == FTW_F) {
        if(S_IXUSR & status->st_mode || S_IXGRP & status->st_mode ||
            S_IXOTH & status->st_mode    
        ) {
            printf("%s : %lld\n", name, status->st_size);
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    ftw(argv[0], list, 1);

    pid_t pid = getpid();
    printf("pid: %d, pgid: %d, sid: %d\n", pid, getpgrp(), getsid(pid));
}