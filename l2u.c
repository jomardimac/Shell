#ifndef L2U_C
#define L2U_C

#include "ucode.c"
char *toUpper(char *c);
void * my_memset(void *s, int c, int n);
main (int argc, char *argv[]){
    int fds, fdd;
    char buf[512], userchar;
    int n, m = 0;
    prints("Jomar's L2U Command!\n");
    if(argc < 0){
        prints("Not valid command");
    }
    //make things uppercase:
    if(argc == 1){
        fds = 0;
        fdd = 1;
        prints("No filename given!\n");
        my_memset(buf, 0, 512);
        while((n = read(fds, buf, 1)) > 0){
            if(n < 0) { 
                break;
            }
            //check for '\n':
            toUpper(buf);
            m = 0;
            while(m < n) {
                if(buf[m] == '\r'){
                    buf[m] = '\n';
                }
                
                write(fdd, &buf[m], 1);
                if(buf[m] == '\n') { 
                    write(2, "\r", 1);
                }
                m++;
            }
        }
        close(fds);
        close(fdd);
        exit(1);

    }
    //make the file uppercase
    if(argc == 2){
        prints("No second file name given");
    }
    else{
        fds = open(argv[1], O_RDONLY);
        fdd = open(argv[2], O_WRONLY | O_CREAT);
        if(fds < 0 || fdd < 0){
            prints("open() failed");
        }
        else{
            //guess we can read it byte by byte and turn it to upper:
            while((n = read(fds, buf, 8192))){
                //check for '\n':
                toUpper(buf);
                m = 0;
                while(m < n){
                    if(buf[m] == '\r' || buf[m] == '\n'){
                        buf[m] = '\n';
                    }
                    
                    write(fdd, &buf[m], 1);
                    m++;
                }
            }
            prints("done with copying to uppercase\n");
            close(fds);
            close(fdd);
        }
    }

    exit(1);
}

#endif
