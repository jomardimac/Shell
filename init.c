#ifndef INIT_C
#define INIT_C
/*init file: p0 creates a child p1 -> loads /bin/init and goes to Umode. 
  p1 executes init program & will allow to fork several login procs. */
#include "ucode.c"

int console;
int parent() {
    int pid, status;
    while(1){
        prints("JOMAR'S INIT\n");
        prints("INIT: waiting for a zombie child.\n");
        pid = wait(&status);
        //console login proc died:
        if(pid == console){
            prints("INIT: forks a new console login");
            //fork another proc:
            console = fork();
            if(console){
                continue;
            }
            //executes new login proc:
            else{
                exec("login /dev/tty0");
            }
        }
        printf("INIT: I just burried an orphan child proc: %d\n", pid);

    }
}

main(){
    int in, out; //file descriptors for terminal i/o
    in = open("/dev/tty0", O_RDONLY); //file descriptor 0
    out = open("/dev/tty0", O_WRONLY); //display console.
    prints("INIT: fork a login proc on console:\n");
    console = fork();
    if(console){
        parent();
    }
    else{
        exec("login /dev/tty0");
    }
}

#endif