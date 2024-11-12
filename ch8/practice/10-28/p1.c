#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<ftw.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/mman.h>

void catchalarm(int);
void catchint(int);
int main(void){
    int i, num, sum=0;
    sigset_t mask;
    static struct sigaction act1, act2;

    // SIGALRM signal 처리가 가능하도록 설정
    act1.sa_handler=catchalarm;
    sigaction(SIGALRM, &act1, NULL);
    // SIGINT signal 처리가 가능하도록 설정
    act2.sa_handler=catchint;
    sigaction(SIGINT, &act2, NULL);
    // SIGINT signal blocking을 위한 준비
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    for (i=0; i<10; i++){
        // SIGINT signal block
        sigprocmask(SIG_SETMASK, &mask, NULL);

        // 10초간 입력이 없으면, SIGALRM이 오도록 설정
        do{
            alarm(10);
        } while(scanf("%d", &num) < 0);
        
        // SIGINT signal unblock
        sigprocmask(SIG_UNBLOCK, &mask, NULL);
        // 입력을 받으면, 알람 꺼두기
        alarm(0);

        sum+=num;
        printf("sum=%d\n", sum);
    }
    exit(0);
}

void catchalarm(int signo){
    printf("input !!! input !!! input !!!\n");
    }
void catchint(int signo){
    printf("Do not interrupt !!!\n");
}