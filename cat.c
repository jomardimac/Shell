#ifndef CAT_C
#define CAT_C

#include "ucode.c"
int main(int argc, char *argv[]){
    prints("JOMARS CAT GOES PURRR\n");
    int n = 0;
    int fd;
    char buf[512], cmdLine[64];
    if(argc < 0){
        prints("No input\n");
        
    }
    //cat the stdin:
    else if(argc == 1){
        prints("No filename given\n");
        n = read(0, buf, 512);
        
    }
    else{
        //open the file, read the file and print the buffer
        strcpy(cmdLine, argv[1]);
        fd = open(cmdLine, O_RDONLY);

        while((n = read( fd, buf, 512))){
            printf("%s", buf);
        }

        close(fd);
    }
}

#endif