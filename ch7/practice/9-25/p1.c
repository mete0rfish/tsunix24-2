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
    int num, i;
    pid_t pid;

    num = atoi(argv[1]);

    for (i=0; i<num; i++){
        pid = fork();
        if (pid == 0){
            do_child();
        }
    }
    for (i=0; i<num; i++){ 
        wait(0);
    }

    return 0;

}