#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>

void ABC(void) {
    printf("ABC ...\n");
    exit(0);
}
void DEF(void) {
    printf("DEF ...\n");
    exit(1);
}
void GHI(void) {
    printf("GHI ...\n");
    exit(2);
}

int main(void) {
    atexit(ABC);
    atexit(DEF);
    atexit(GHI);
    exit(15);
}