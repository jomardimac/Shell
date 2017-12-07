#ifndef GREP_C
#define GREP_C

#include "ucode.c"

int E_OF = 1;

int strncmp(char * s1, const char *s2, int i);
char *findSubstr(char *substr, char *src);
void * my_memset(void *s, int c, int n);

int main(int argc, char *argv[1]){
    int fd;
    int n, line;
    int LINES = 80;
    char pat[64], buf[128];
    prints("************Jomar's GREP Command!***********\n");
    if(argc < 1){
        prints("Pattern required\n");
        exit(1);
    }
    else if(argc == 2){
        //prints("No filename given\n");
        strcpy(pat, argv[1]);
        fd = dup(0);

        //go through the file:
        while(E_OF == 1){
            my_memset(buf, 0, 128);
            //go through a line and see if 'pattern' matches:
            line = 0;
            while(line < LINES){
                n = read(fd, &buf[line], 1);
                //end of file:
                if(n == 0) {
                    E_OF = 0;
                }
                //end of line, with root
                else if(buf[line] == '\n' || buf[line] == '\r') {
                    buf[line + 1] = 0;
                    break;
                }
                line ++;
                
            }
            //printf("%s", buf); //testing buffer.
            if(findSubstr(pat, buf) != 0){
                printf("%s", buf);
            }
        }
        close(fd);
    }

    //open file name up and start looking for lines with pattern:
    else{
        strcpy(pat, argv[1]);
        if((fd = open(argv[2], O_RDONLY)) < 0){
            prints("open() failed\n");
            exit(1);
        }

        //go through the file:
        while(E_OF == 1){
            my_memset(buf, 0, 128);
            //go through a line and see if 'pattern' matches:
            line = 0;
            while(line < LINES){
                n = read(fd, &buf[line], 1);
                //end of file:
                if(n == 0) {
                    E_OF = 0;
                }
                //end of line, with root
                else if(buf[line] == '\n' || buf[line] == '\r') {
                    buf[line + 1] = 0;
                    break;
                }
                line ++;
                
            }
            //printf("%s", buf); //testing buffer.
            if(findSubstr(pat, buf) != 0){
                printf("%s", buf);
            }
        }
        close(fd);
    }
}



#endif