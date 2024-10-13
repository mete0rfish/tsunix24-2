#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>
#include <signal.h>

void do_child(int i, pid_t *cid){
    // SIGUSR1 signal 처리가 가능 하도록 설정
    int j;
    pid_t pid;
    static struct sigaction act;

    act.sa_handler=SIG_DFL;
    sigaction(SIGUSR1, &act, NULL);

    // 자신의 출력 순서가 될 때까지 대기
    pause();

    pid=getpid();
    for (j=0;j<5;j++){
        printf("child %d .... \n", pid);
        sleep(1);
    }
    
    // 출력 완료 후 다음 출력 순서의 child에게 출력 시작을 알림
    kill(cid[i+1], SIGUSR1);

    exit(0);
}

int main(void) {
    int i, status;
    pid_t pid[5];
    for (i=0;i<5;i++){
        pid[i]=fork();
        if (pid[i]==0) {
            do_child(i, pid);   
        }
        for (i=0;i<5;i++){
            wait(&status);
            }
    }
    exit(0);
}