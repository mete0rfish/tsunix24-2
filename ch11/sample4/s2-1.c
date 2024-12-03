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

int main(int argc, char** argv) {
    int semid, n, k;
    key_t key;
    union semun arg;
    struct sembuf p_buf = {0, -1, 0};

    key=ftok("key", 7);
    semid=semget(key, 1, 0600|IPC_CREAT|IPC_EXCL);
    if(semid == -1) {
        semid = semget(key, 1, 0600);
    }
    else {
        arg.val = 1;
        semctl(semid, 0, SETVAL, arg);
    }

    printf("process %d : %d --> ", getpid(), semctl(semid, 0, GETVAL, 0));
    semop(semid, &p_buf, 1);
    printf("%d\b", semctl(semid, 0, GETVAL, 0));

    return 0;
}