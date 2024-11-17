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

#define MSGSIZE 6
char *msg1 = "hello";
char *msg2 = "bye!!";
void parent(int[][2]);
int child(int[]);

int main(void){
    int pip[3][2];
    int i;
    for (i=0; i<3; i++) {
        pipe(pip[i]);
        if(fork()==0)
            child(pip[i]);
    }
    parent(pip);
    for (i=0; i<3; i++) {
        wait(0);
    }
    exit(0);
}

void parent(int p[3][2]){
    char buf[MSGSIZE], ch;
    fd_set set, master;
    struct timeval t;
    int i, j, k,n;
    for (i=0; i<3; i++)
        close(p[i][1]);
    FD_ZERO(&master);
    for (i=0; i<3; i++)
        FD_SET(p[i][0], &master); // Master {p[0][0], p[1][0], p[2][0]} 모든 읽기
    t.tv_sec=5;
    while (set=master, select(p[2][0]+1, &set, NULL, NULL, &t) > 0) {
        for (i=0; i<3; i++){
            if (FD_ISSET(p[i][0], &set)){// set 집합에 p[i][0]이 포함되어 있는지?
                if ((n=read(p[i][0], buf, MSGSIZE)) >0)
                    printf("MSG from %d=%s\n", i, buf);
                else if(n==0) // writer가 없으면 read 시, 0 반환 -> select는 0이더라도 있다고 판단
                    FD_CLR(p[i][0], &master); // master 비트를 0으로 만들어서 검사하지 않도록 함 -> 3이 종료되면 0으로 만들어서 종료되도록
                // 타임아웃되는 시간이 재각각 -> select 문 리턴 시, set 깂이 변경됨 -> 타이머 값도 변경됨
                // 따라서, while 문 끝날 때마다 재설정
            }
        }
        t.tv_sec=5;
    }
}
int child(int p[2]){
    int count;
    close(p[0]);
    for (count=0; count<2; count++){
        write(p[1], msg1, MSGSIZE);
        sleep(getpid()%4);
    }
    write(p[1], msg2, MSGSIZE);
    exit(0);
}