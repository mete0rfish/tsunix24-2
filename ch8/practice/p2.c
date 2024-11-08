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

void func(int signo) {

}

void do_child(int i, pid_t *cid){
    // SIGUSR1 signal 처리가 가능 하도록 설정
    int j;
    pid_t pid;
    static struct sigaction act;

    act.sa_handler=func;
    sigaction(SIGUSR1, &act, NULL);

    // 자신의 출력 순서가 될 때까지 대기
    if(i<4)
        pause();

    pid=getpid();
    for (j=0;j<5;j++){
        printf("child %d .... \n", pid);
        sleep(1);
    }
    
    // 출력 완료 후 다음 출력 순서의 child에게 출력 시작을 알림
    if(i>0)
        kill(cid[i+1], SIGUSR1);

    exit(0);
}

/*
0,1,2,3,4 순으로 차일드끼리 동기화 하라고 하면
-> 지금이 코드에선 가능하지 않음
pid 넘겨주는 시점에서 다음 child id를 알 수 없음

순서 바꾸려면 id를 어떻게 받아야 할까?
*/

int main(void) {
    int i, status, cid;
    pid_t pid[5];
    for (i=0;i<5;i++){
        pid[i]=fork();
        if (pid[i]==0) {
            do_child(i, pid);   
        }
    }

    for (i=0;i<5;i++){
        cid = wait(&status);
        porintf("child id=%d, exit status=%d\n",  cid, WEXITSTATUS(status));
    }
    exit(0);
}