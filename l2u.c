#ifndef L2U_C
#define L2U_C

#include "ucode.c"
char *toUpper(char *c);
main (int argc, char *argv[]){
    int fds, fdd;
    char buf[8192], userchar;
    int n, m = 0;
    prints("Jomar's L2U Command!\n");
    if(argc < 0){
        prints("Not valid command");
    }
    //make things uppercase:
    if(argc == 1){
        prints("No filename given!\n");

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
}


//ascii numbers from a-z (97-122)
char *toUpper(char *str){
    int i = 0;
    while(*str++){
        if(str[i] <= 122 && str[i] >= 97){
            str[i] = str[i] - 32;
        }
    }
    return str;
}
#endif
