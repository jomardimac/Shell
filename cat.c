#ifndef CAT_C
#define CAT_C

#include "ucode.c"
void * my_memset(void *s, int c, int n);
int main(int argc, char *argv[]){
    prints("JOMARS CAT GOES PURRR\n");
    int n = 0, i = 0;
    int fd, stdin = 0, stdout = 1;
    char buf[512], cmdLine[64], userch;
    if(argc < 0){
        prints("No input\n");
        exit(1);
    }
    //cat the stdin:
    else if(argc == 1){
        prints("No filename given\n");
        fd = 0;
        while(read(0, buf, 1)){
            //check for enter line and add the line in stdout
            if(buf[0] == '\n'){
                write(1, "\n", 1);
                write(1, "\r", 1);
            }
            //if not, then just put the char in screen:
            else{
                write(1, buf, 1);
            }
            //write(stdout, &userch, 1);
        }
    }
    else{
        //open the file, read the file and print the buffer
        fd = open(argv[1], O_RDONLY);
        my_memset(buf, 0, 512);
        while((n = read( fd, buf, 512))){
            prints(buf);
            my_memset(buf, 0, 512);
            //write(fd, buf, n);
        }
        close(fd);
    }
}

#endif