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
    int i, n, status;
    pid_t pid[3];
    for (i=0; i<3; i++){
        pid[i] = fork();
        if (pid[i] == 0){
            do_child(i);
        }
    }
    for (i=2;i>=0;i--) {
        // 세 child의 종료 상태를 child 생성 순서의 역순으로 확인
        n = waitpid(pid[i], &status, 0);
        if (WIFEXITED(status)) {
            printf("%d......%d\n", n, WEXITSTATUS(status));
        }
    }
    exit(0);
}