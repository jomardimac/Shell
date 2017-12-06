#ifndef SH_C
#define SH_C

#include "ucode.c"

void do_pipe(char *cmdl);
char *mystrtok(char *source, const char *delimeter);
void * my_memset(void *s, int c, int n);

int status;

int main(int argc, char *argv[]) {
    char cmdline[128], temp[128], *tok;
    int pid;
    int *r;
    while(1) {
        prints("***************************\n");
        prints("This is Jomar's unexiciting Shell\n");
        prints("***************************\n");
        char curdir[128];
        getcwd(curdir);
        //grab my commands: 
        printf("Jomar-SH: %s# ", curdir);
        gets(cmdline);

        //dont want ot mess around with the cmd so i'll save it in a temporary buffer:
        strcpy(temp, cmdline);
        if(cmdline[0] == 0 || cmdline[0] == ' '){
            continue;
        }
        //grab the cmds itself:
        tok = mystrtok(temp, " ");
        printf("Tok: %s\n", tok);
        
        //*****************DIRECTORY HANDLING AND LOGGING OUT ***************************//
        if(strcmp(tok, "cd") == 0) {
            tok = mystrtok(0, " ");

            //no dir enter:
            if(tok == 0){
                prints("Just pwd! \n");
                chdir(curdir);
            }

            else {
                printf("change dir to = %s\n", tok);
                chdir(tok);
            }
        }
        else if(strcmp(tok, "logout") == 0 ){
            prints("loggin out\n");
            chdir("/");
            exit(0);
        }
        else if (strcmp(tok, "pwd") == 0){
            pwd();
        }
        //******************END OF COMMON DIRECTORY AND LOGGOUT **************************//

        else {
            //we fork!
            prints("Fork a child proc to run the command!\n");
            pid = fork();
            
            if(pid < 0){
                prints("fork() failed, no child proc\n");
                exit(0);
            }

            prints("Fork successful: we now execute  ");
            if(pid) {
                //do child first
                printf("Parent id: %d forked child: %d ... waiting for it to die\n", getpid(), pid);
                pid = wait(&status);
                printf("child %d done with proc BACK TO SHELL!\n", pid);                
            }
            else {
                printf("\n\nCOMMANDLINE = %s \n\n", cmdline);
                if(pipeFound(cmdline) == 0){
                    exec(cmdline);
                }
                else{
                    prints("***************************PIPING!***********\n");
                    do_pipe(cmdline);
                }
            }
        }

        //****************************DONE WITH EXEC/PIPE! *******************************//
        my_memset(curdir, 0, 128);
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
    int i = 0, j = 0;
    char *tok, *cmd1, *cmd2;
    char head[128], tail[128], temp[128];
    strcpy(temp, cmdl);

    //grab  first commands:
    while(temp[i] != '|' ) {
        head[i] = temp[i];
        i++;
    }
    head[i - 1] = 0;

    // cmd1 = mystrtok(temp, "|");
    // strcpy(head, cmd1);
    //grab second:
    i = 0; j = 0;
    while(temp[i] != '|') { 
        i++;
    }
    i += 2;
    
    while(temp[i] != 0 ) {
        tail[j] = temp[i];
        i++;j++;
    }
    tail[j] = 0;
    
    printf("Head: %s\n", head);
    printf("Tail: %s\n", tail);
    
    pipe(pd); //create a pipe: pd[0] = READ, pd[1] = WRITE
    pid = fork(); //fork a child to share the pipe.

    //PARENT PROC:
    if(pid){ //parent = reader
        close(pd[1]); //close the pip read
        dup2(pd[0], 0);   //redirect stdout to pipe write
        

        if(pipeFound(tail) != 0) {
            printf("Found a pipe: %s\n", tail);
            do_pipe(tail);
            
        }
        else {
            exec(tail);
            
        }
    }
    //CHILD PROC:
    else { //child = pipe
        close(pd[0]);   //close WRIT:
        dup2(pd[1], 1); //reopen write
        exec(head);
        
    }

    return;
}

int pipeFound(char *cmdl){
    char *c = cmdl;

    while(*c){
        if(*c == '|'){
            return 1;
        }
        *c++;
    }
    return 0;
}

#endif