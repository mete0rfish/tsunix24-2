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
    int semid, n, i;
    key_t key;
    union semun arg;
    ushort buf1 [3] = {1,2,3}, buf2[3] = {0};
    struct sembuf p_buf[2] = {{0, -1, 0}, {1, -1, 0}};
     
    key = ftok("key", 3);
    semid=semget(key, 3, 0600|IPC_CREAT);

    arg.array=buf1;
    printf("SETALL ...%d\n", semctl(semid, 0, SETALL, arg));

    arg.array = buf2;
    printf("GETALL ...%d\n", semctl(semid, 0, GETALL, arg));
    for(i=0;i<3;i++)    printf("%d\n", arg.array[i]);

    semop(semid, p_buf, 2);

    printf("GETALL ... %d\n", semctl(semid, 0, GETALL, arg));
    for(i=0;i<3;i++)    printf("%d\n", arg.array[i]);

    sleep(10);

    return 0;
}