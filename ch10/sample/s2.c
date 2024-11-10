#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>

int main() {
    int i, in, pid, p[2][2];
    int status;
    for(i=0;i<2;i++) {
        pipe(p[i]);
    }

    pid = fork();
    if(pid == 0) {
        close(p[0][1]);
        close(p[1][0]);
        
        for (i = 0; i < 3; i++) {
            if(read(p[0][0], &in, sizeof(int))) {
                printf("child reads %d ... \n", in);
                in++;
                printf("child writes %d ... \n", in);
                write(p[1][1], &in, sizeof(int));
            }
            else {
                printf("child reads 0 ... \n");
            }
        }

        exit(0);
    }

    close(p[0][0]);
    close(p[1][1]);

    for(i=0;i<3;i++) {
        scanf("%d", &in);
        printf("parent writes %d ... \n", in);
        write(p[0][1], &in, sizeof(int));
        if(i<2) {
            read(p[1][0], &in, sizeof(int));
            printf("parent reads %d ... \n", in);
        }
        else {
            close(p[1][0]); // 읽기 닫기
        }
    }
    /*
     * 부모 : writer , 자식 : reader
     * 더 이상 reader가 없는 경우, writer들은 SIGPIPE 시그널 받음 (즉발)
     */
    wait(&status);
    if(WIFEXITED(status)) {
        printf("exits ... %d\n", WEXITSTATUS(status));
    }
    else if(WIFSIGNALED(status)) {
        printf("terminated ... %d\n", WTERMSIG(status));
    }
    exit(0);
}