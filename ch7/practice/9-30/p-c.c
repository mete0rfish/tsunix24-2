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

    // ~/bin은 PATH에 등록되어 있기 때문에 실행 가능
    execlp("test2", "test2", "abc", "def", "ghi", (char*)0);
    
    exit(0);
    return 0;
}