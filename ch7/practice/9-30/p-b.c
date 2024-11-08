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

    execl("test1", "test1", "abc", "def", "ghi");
    
    exit(0);
    return 0;
}