#ifndef CP_C
#define CP_C

#include "ucode.c"
main(int argc, char *argv[]){
    int fds, fdd;
    char buf[8192];
    int n, m = 0;
    prints("Jomar's cp command!\n");
    //no source or dest:
    if(argc < 3){
        prints("Not valid command\n");
    }
    
    else {
        //open up the two command lines 
        fds = open(argv[1], O_RDONLY);
        fdd = open(argv[2], O_WRONLY | O_CREAT);
        if(fds < 0 || fdd < 0) {
            prints("open() failed");
        }
        else {
            //read n byetes from source save it to buf
            //, write to dest n bytes from buf
            while((n = read(fds, buf, 8192))){
                printf("n = %d bytes ", n);
                write(fdd, buf, n);
                m += n;
            }
            printf("%d bytes copied\n", m);
            //close after done reading and writing:
            close(fds);
            close(fdd);
        }
        
    }

    
}

#endif