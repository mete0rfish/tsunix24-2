#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>

void cd_m(char **res) {
    int flag = chdir(res[1]);
    if(flag == -1) {
        printf("No such Directory.\n");
    }
    else {
        printf("changed to %s\n", res[1]);
    }
}

void mkdir_m(char **res) {
    printf("created directory\n");
    mkdir(res[1], 0700);
}

void ls_m(char **res) {
    DIR* dp;
    struct dirent *d;

    dp = opendir(".");
    d = readdir(dp);
    while(d!=NULL) {
        if(d->d_name[0]!='.') {
            printf("%ld : %s\n", d->d_ino, d->d_name);
        }
        d = readdir(dp);
    }
}

int main(void) {
    // main 함수는 수정하지 말고, 사용하세요.
    char in[100], *res[20] = {0};
    char *inst[3] = {"cd", "mkdir", "ls"};
    void (*f[3])(char **) = {cd_m, mkdir_m, ls_m};
    int i;
    while (1) {
        getcwd(in, 100);
        printf("%s> ", in);
        gets(in);
        if (in[0] == '\0')
            continue;
        i = 0;
        res[i] = strtok(in, " ");
        while (res[i]) {
            i++;
            res[i] = strtok(NULL, " ");
        }
        if (strcmp(res[0], "exit") == 0)
            exit(0);
        for (i = 0; i < 3; i++) {
            if (!strcmp(res[0], inst[i])) {
                f[i](res);
                break;
            }
        }
    }
    return 0;
}
