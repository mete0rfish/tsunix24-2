#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <ftw.h>

int main(int argc, char ** argv) {
    char * vec[5] = {"test2", "abc", "def", "ghi", (char*)0};
    execv("test2", vec);
    
    exit(0);
    return 0;
}