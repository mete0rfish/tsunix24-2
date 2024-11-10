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

    for(i=0;i<2;i++) {
        scanf("%d", &in);
        printf("parent writes %d ... \n", in);
        write(p[0][1], &in, sizeof(int));
        read(p[1][0], &in, sizeof(int));
        printf("parent reads %d ... \n", in);
    }

    close(p[0][1]);
    
    wait(0);
    exit(0);
}