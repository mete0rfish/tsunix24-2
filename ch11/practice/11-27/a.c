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
#include <sys/shm.h>
#include <sys/sem.h>

int main() {
    int shmid, semid, i, n, *buf;
    key_t key1, key2;
    union semun arg;
    struct sembuf p_buf;

    key1 = ftok("key", 1);
    semid = semget(key1, 1, IPC_CREAT | 0666);
    if(semid == -1) {
        semget(key1, 1, 0);
    }
    else {
        arg.val = 0;
        semctl(semid, 0, SETVAL, arg);
    }

    key2 = ftok("key", 2);
    shmid = shmget(key2, 512, IPC_CREAT | 0666);
    buf = shmat(shmid, NULL, 0);


    for(i=0;i<10;i++) {
        scanf("%d", buf+i);
        p_buf.sem_num = 0;
        p_buf.sem_op = 1;
        p_buf.sem_flg = 0;
        semop(semid, &p_buf, 1);
        sleep(1);
    }

    shmdt(buf);
    exit(0);
}