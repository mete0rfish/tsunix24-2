#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>

int main(void) {
    int in[10]={1,2,3,4,5}, fd, i, p, N,n;

    fd=open("data1", O_RDWR | O_CREAT, 0600);

    p=lseek(fd, 0, SEEK_SET);
    printf("%d\n", p);
    p=lseek(fd, 0, SEEK_END);
    printf("%d\n", p);
    p=lseek(fd, 0, SEEK_CUR);
    printf("%d\n", p);

    for(i=0;i<5;i++) {
        write(fd, in+i, sizeof(int));
        p=lseek(fd, 0, SEEK_CUR);
        printf("%d\n", p);
    }

    p=lseek(fd, 0, SEEK_SET);
    printf("%d\n", p);
    p=lseek(fd, 0, SEEK_END);
    printf("%d\n", p);


    p=lseek(fd, -4, SEEK_END);
    read(fd, &N, sizeof(int));
    printf("%d ... %d",p,N);
    p=lseek(fd, 0, SEEK_CUR);
    printf(" ... %d\n", p);


    p=lseek(fd, +4, SEEK_END);
    n=read(fd, &N, sizeof(int));
    printf("%d ... %d ... %d\n", p, N,n);
    write(fd, in, sizeof(int));
    p=lseek(fd, 0, SEEK_CUR);
    printf("%d\n", p);

    lseek(fd,0,SEEK_SET);
    for(i=0;i<10;i++){
        n=read(fd, &N, sizeof(int));
        printf("%d ... %d\n", N, n);
    }

    p=lseek(fd, -4, SEEK_SET);
    printf("%d\n", p);
    p=lseek(fd, +4, SEEK_SET);
    printf("%d\n", p);

    return 0;
}
