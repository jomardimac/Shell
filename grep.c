#ifndef GREP_C
#define GREP_C

#include "ucode.c"

int main(int argc, int argv[1]){
    int fd;
    int n;
    char pat[64], buf[1024];

    if(argc < 1){
        prints("Pattern required\n");

    }
    else if(argc == 2){
        prints("No filename given\n");
    }

    //open file name up and start looking for lines with pattern:
    else{
        strcpy(pat, argv[1]);
        fd = open(argv[2], O_RDONLY);

        //go through the file:
        while((n =  read(fd, buf, 1024))) {
            
        }
    }
}

#endif