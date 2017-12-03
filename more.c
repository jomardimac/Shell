#ifndef MORE_C
#define MORE_C

#include "ucode.c"
int main(int argc, char *argv[]){
    int n = 0;
    int fd;

    char buf[1028], cmdline[64];
    if(argc < 0){
        prints("Nothing inputted\n");

    }
    else if(argc == 1){
        prints("No file selected\n");

    }
    else{
        fd = open(argv[1], 0);
        while(n = (read(fd, buf, 1028)){
            printf("%s", buf);
            
            if(n == 80){
                prints("\n");
                getc();
                
            }
        }
    }
}
#endif