#include <dirent.h> //dir
#include <errno.h> //errno

#include <stdio.h>
#include <stdlib.h>

int main(){
    DIR* dir = opendir("C:/Users/user/Desktop/New folder");
    if (dir) {
        /* Directory exists. */
        printf("dir exists");
        closedir(dir);
    } else if (ENOENT == errno) {
        /* Directory does not exist. */
        printf("Dir does not exists");
    } else {
        /* opendir() failed for some other reason. */
        printf("faild to open, some other reasons");
    }

    return 0;
}
