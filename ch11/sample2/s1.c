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

struct databuf {
    int d_nread;
    char d_buf[512];
};

int main() {
    char *buf1;
    int i, n, shmid1, shmid2, shmid3, *buf2;
    key_t key1, key2, key3;
    struct databuf *buf3;

    key1=ftok("key", 1);
    key2=ftok("key", 2);
    key3=ftok("key", 3);
    
    shmid1=shmget(key1, 512, 0600|IPC_CREAT);
    shmid2=shmget(key2, sizeof(int)*10, 0600|IPC_CREAT);
    shmid3=shmget(key3, sizeof(struct databuf) * 5, 0600|IPC_CREAT);

    buf1=(char*)shmat(shmid1,0,0);
    buf2=(int*)shmat(shmid1,0,0);
    buf3=(struct databuf*)shmat(shmid1,0,0);

    n = read(0, buf1, 512);
    write(1, buf1, 512);

    for(i=0;i<10;i++)
        scanf("%d", buf2+i);
    for(i=0;i<10;i++)
        printf("%d\n", *(buf2+i));

    for(i=0;i<5;i++){
        n=read(0, (buf3+i)->d_buf, 512);
        (buf3+i)->d_nread=n;
    }
    for(i=0;i<5;i++)
        printf("%d ... %s\n", (buf3+i)->d_nread, (buf3+i)->d_buf);

    shmctl(shmid1, IPC_RMID, 0);
    shmctl(shmid2, IPC_RMID, 0);
    shmctl(shmid3, IPC_RMID, 0);
}