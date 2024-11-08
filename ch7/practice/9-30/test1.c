#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>

void do_child() {
    pid_t pid = getpid();
    printf("%ld %ld %ld\n", pid, getpgid(pid), getsid(pid));
    exit(0);
}

int main(int argc, char **argv) {
    int i, j;

    for (i=0; i<3; i++){
        for(j=1;j<4;j++) {
            printf("%s\n", argv[j]);
        }
    }

    return 0;

}