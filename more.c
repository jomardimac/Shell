#ifndef MORE_C
#define MORE_C

#include "ucode.c"
void printLine(int fd);
void printChar(int fd);
void printPage(int fd);
int endoffile = 1;
int main(int argc, char *argv[]){
    //80 characters in a line
    int n = 0, line = 80, page = 20;
    int fd;
    int stdin = 0, stdout = 1;
    char tty[128];

    prints("JOMAR'S MORE MAN!\n");
    char buf[1600], cmdline[64], userch, c;

    if(argc < 0){
        prints("Nothing inputted\n");

    }

    else if(argc == 1){
        prints("No file selected\n");
        //do mroe in stdin and stdout:
        fd = dup(0);
        close(0);

        //gettty(tty); //read:
        open(tty, O_RDONLY);
        endoffile = 1;
        while(endoffile != 0) {
            userch = getc();
            //printf("\nTHIS IS THE CHAR PRESSED %c\n", userch);
            //'\n' is a line, ' ' is a whole page, else is next char
            if(userch == '\r'){
                printLine(fd);
            }
            else if( userch == ' ') {
                printPage(fd);
            }
            else {
                printChar(fd);
            }
        }
        close(fd); 
    }
    else{
        //open file:
        strcpy(cmdline, argv[1]);
        fd = open(cmdline, 0);
        //read file and store in buf then print:
        //but first, print out the whole page:
        printPage(fd);
        while(endoffile != 0) {
            userch = getc();
            //printf("\nTHIS IS THE CHAR PRESSED %c\n", userch);
            //'\n' is a line, ' ' is a whole page, else is next char
            if(userch == '\r'){
                printLine(fd);
            }
            else if( userch == ' ') {
                printPage(fd);
            }
            else {
                printChar(fd);
            }
        }
    
        close(fd); 
    }
    
}

void printPage(int fd){
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
            //check if it can't be read
            if(n == 0){
                endoffile = 0;
                return;
            }
            if(c != '\n' || c != '\r'){
                mputc(c);
            }
            //mputc(c);
            
            byt++;
        }
        
        line++;
    }
    mputc('\n');
}

void printChar(int fd){
    char c;
    int n = read(fd, &c, 1);
    if(n == 0){
        endoffile = 0;
        return;
    }
    if(c != '\n' || c != '\r'){
        mputc(c);
    }
    
}

void printLine(int fd){
    int byt = 0, n = 0;
    int CHARS = 80;
    char c;

    byt = 0;
    //read 80 bytes in a line:
    while(byt < CHARS){
        //read the char:
        n = read(fd, &c, 1);
        if(n == 0){
           endoffile = 0;
           return; 
        }
        
        mputc(c);
        byt++;
    }
    
    mputc('\n');
}
#endif