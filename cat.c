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

        while(read(stdin, &userch, 1)){
            //check for enter line and add the line in stdout
            if(userch == '\n' || userch == '\r'){
                write(stdout, "\n", 1);
                write(stdout, "\r", 1);
            }
            //if not, then just put the char in screen:
            else{
                write(stdout, &userch, 1);
            }
        }
    }
    else{
        //open the file, read the file and print the buffer
        strcpy(cmdLine, argv[1]);
        fd = open(cmdLine, O_RDONLY);
        my_memset(buf, 0, 512);
        while((n = read( fd, buf, 512))){
            printf("%s", buf);
        }
        my_memset(buf, 0, 512);
        close(fd);
    }
}

#endif