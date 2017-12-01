#ifndef LOGIN_C
#define LOGIN_C

#include "ucode.c"

//login.c : upon entry, argv[0] = login, argv[1] = tty

int in, out, err;
char usrname[128], password[128], homedir[256], prog[256];
int uid, gid;

main(int argc, char  *argv[]) {
    prints("JOMAR'S LOGIN EXEC PROC \n");
    // close file descriptors 0,1,2, from init which are.
    //0 = standard in, 1 = standard out, 2 = standard error
    close(0); close(1); close(2);

    //open argv[1] for in(0), out(1), err(2):
    in = open(argv[1], 0);
    out = open(argv[1], 1);
    err = open(argv[1], 2);

    //set tty name string in PROC.tty:
    fixtty(argv[1]);

    //open /etc/password for READ:
    while(1){
        prints("Username: "); 
        gets(usrname);
        prints("Password: "); 
        gets(password);
        printf("inputed Username: %s \n", usrname);
        printf("inputted Password: %s \n", password);
        //foreach line in /etc/password file do{
        // tokenize user account line;
        // if valid{
        // change uid, gid to user's uid, gid; chuid();
        // change cwd to user's home DIR chdir();
        // close opened /etc/passwd file: //close();
        //  exec to program in user account: exec(); 
        //}            }

        //check and see if etc/password can be read:
        int fd, fdLen;
        char fdBuf[256];
        if((fd = open("/etc/passwd", 0))< 0){
            prints("Can't open() etc/password\n");
            exit(1);
        }
        //now read file discriptor:
        if((fdLen = read(fd, fdBuf, 256))< 0){
            prints("Can't read() pswd file!\n");
            exit(1);
        }
        
        //we can now tokenize each password and see if it matches:
        bool valid = false;
        char *tok = strtok(buf, ":\n"); //grab username.
        while(tok != NULL){
            //compare both file's username & see if its valid:
            if(strcmp(tok,usrname) == 0){
                prints("Valid username!\n");
                //compare both file's password & username:
                tok = strtok(NULL, ":\n");
                
                if(strcmp(tok, password) == 0){
                    prints("Valid password! \n");
                    //set everything:
                    valid = true;
                    //originally string so change to int:
                    uid = atoi(strtok(NULL, ":\n"));
                    gid = atoi(strtok(NULL, ":\n"));
                    strcpy(usrname, strtok(NULL, ":\n"));
                    strcpy(homedir, strtok(NULL, ":\n"));
                    strcpy(prog, strtok(NULL, ":\n"));
                    chuid(uid, gid);
                    chdir(homedir);
                    exec(prog);
                    close(file);
                }
            }

            tok = strtok(NULL, ":\n");
        }
    }

    prints("Login failed, try again\n");

}

#endif