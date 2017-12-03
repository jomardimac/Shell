#ifndef CP_C
#define CP_C

#include "ucode.c"
main(int argc, char *argv[]){
    int fds, fdd;
    char src[8192], dest[8192];
    //no source or dest:
    if(argc < 3){
        prints("Not valid command");
    }
    
    else {
        //open up the two command lines 
        if((fds = open(argv[1], 0)< 0)  && fdd = open(argv[1], O_WRONLY | O_CREAT) < 0)){
            printf("open() failed");
        }
        else{
            //read n byetes from source, write to dest n bytes
            while(n = read(fds, buf, 8192)){
                write(fdd, buf, n)
            }
            close(fds);
            close(fdd);
        }
        
    }

    
}

#endif