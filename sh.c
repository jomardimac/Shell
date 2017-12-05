#ifndef SH_C
#define SH_C

#include "ucode.c"

int main(int argc, char *argv[]) {
    char cmdline[128], temp[128];
    while(1) {
        prints("***************************\n");
        prints("This is Jomar's unexiciting Shell\n");
        prints("***************************\n");
        char curdir[128];
        getcwd(curdir);
        printf("Jomar-SH: %s$", curdir);
        gets(cmdline);

        //do the line:
        strcpy(temp, cmdline);
        


    }
}

/* do_pipe Algorithm ************
    int pid, pd[2];
    pipe(pd); // create a pipe: pd[0]=READ, pd[1]=WRITE
    pid = fork(); // fork a child to share the pipe
    if (pid){ // parent: as pipe READER
    close(pd[1]); // close pipe WRITE end
    dup2(pd[0], 0); // redirect stdin to pipe READ end
    exec(cmd2);
    }
    else{ // child : as pipe WRITER
    close(pd[0]); // close pipe READ end
    dup2(pd[1], 1); // redirect stdout to pipe WRITE end
    exec(cmd1);
    }
    Multiple pipes are handled recursively, from right to left
*/

void do_pipe(char *cmdl) {
    int pid, pd[2];
    char *tok, *cmd1, *cmd2;
    char head[128], tail[128];
    //grab  first commands:
    cmd1 = strtok(cmdl, "|");
    strcpy(head, cmd1);
    //grab second:
    cmd2 = strtok(0, "\n");
    strcpy(tail, cmd2);


    pipe(pd); //create a pipe: pd[0] = READ, pd[1] = WRITE
    pid = fork(); //fork a child to share the pipe.

    //PARENT PROC:
    if(pid){ //parent = reader
        close(0); //close the pip write
        dup(pd[0], 0);   //redirect stdout to pipe write
        exec(tail);
    }
    //CHILD PROC:
    else { //child = pipe
        close(1);   //close WRIT:
        dup2(pd[1], 1); //reopen write
        exec(head);
    }
}


#endif