#ifndef MORE_C
#define MORE_C

#include "ucode.c"
int main(int argc, char *argv[]){
    int n = 0;
    int fd;
    prints("JOMAR'S MORE MAN!\n");
    char buf[128], cmdline[64];
    if(argc < 0){
        prints("Nothing inputted\n");

    }
    else if(argc == 1){
        prints("No file selected\n");

    }
    else{
        //open file:
        strcpy(cmdline, argv[1]);
        fd = open(cmdline, 0);
        //read file and store in buf then print:
        while((read(fd, buf, 128))){
            printf("%s", buf);
            //Clear the previous string saved in buf:
            getc();
        }
        
    }
    close(fd);
}
#endif