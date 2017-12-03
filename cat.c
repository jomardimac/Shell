#ifndef CAT_C
#define CAT_C

#include "ucode.c"
int main(int argc, char *argv[]){
    prints("JOMARS CAT GOES PURRR");
    int n = 0;
    int fd;
    //struct stat sp;
    char buf[512], cmdLine[64];
    if(argc < 0){
        prints("No input\n");
        
    }
    else if(argc == 1){
        prints("No filename given\n");
    }
    else{
        
        strcpy(cmdLine, argv[1]);
        if(fd = open(cmdLine, 0)){
            prints("open() failed\n");
        }

        while((n = read( fd, buf, 512))){
            printf("%s", buf);
        }

        close(fd);
    }
}

#endif