#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>

void do_child(int N){
    int i;
    pid_t pid = getpid();
    for (i=0; i<5; i++){
        printf("%ld %ld %ld\n", pid, getpgid(pid), getsid(pid));
        sleep(1);
    }
    exit(N);
}

int main(void){
    int i, status;
    pid_t pid;
    for (i=0; i<3; i++){
        pid = fork();
        if (pid == 0 && i == 0){
            execl("printStr", "printStr", "abc");
            exit(0);
        }
        else if (pid == 0 && i == 1){
            execl("printStat", "printStat");
            exit(0);
        }
        else if (pid == 0 && i == 2){
            execl("printData", "printData");
            exit(0);
        }
    
    }
    for (i=0; i<3; i++){
        wait(&status);
        printf("%d closed\n", i);
    }
    exit(0);
    
}