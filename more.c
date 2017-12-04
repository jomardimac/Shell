#ifndef MORE_C
#define MORE_C

#include "ucode.c"
int main(int argc, char *argv[]){
    //80 characters in a line
    int n = 0, line = 80, page = 20;
    int fd;
    int stdin = 0, stdout = 1;
    
    prints("JOMAR'S MORE MAN!\n");
    char buf[1600], cmdline[64], userch, c;

    if(argc < 0){
        prints("Nothing inputted\n");

    }

    else if(argc == 1){
        prints("No file selected\n");
        while(read(stdin, &userch, 1)){
            write(stdout, &userch, 1);
        }
    }
    else{
        //open file:
        strcpy(cmdline, argv[1]);
        fd = open(cmdline, 0);
        //read file and store in buf then print:
        //but first, print out the whole page:
        printPage(fd);
        while(1) {
            userch = getc();
            //printf("\nTHIS IS THE CHAR PRESSED %c\n", userch);
            //'\n' is a line, ' ' is a whole page, else is next char
            if(userch == '\r'){
                //printLine(fd);
            }
            else if( userch == ' ') {
                printPage(fd);
            }
            else {
                printChar(fd);
            }
        }
    
        
    }
    close(fd);
}

printPage(int fd){
    int line = 0, byt = 0, n = 0;
    int LINES = 10, CHARS = 80;
    char c;

    //20 lines total in a page:
    while(line < LINES){
        byt = 0;
        //read 80 bytes in a line:
        while(byt < CHARS){
            //read the char:
            n = read(fd, &c, 1);
            mputc(c);
            byt++;
        }
        
        line++;
    }
    mputc('\n');
}

printChar(int fd){
    char c;
    read(fd, &c, 1);
    mputc(c);
}

#endif