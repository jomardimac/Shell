#ifndef CAT_C
#define CAT_C

int main(int argc, char *argv[]){
    int n = 0;
    struct stat sp;
    char buf[8192];
    while((n = read( 0, buf, O_RDONLY)) > 0){
        printf("%s", buf);
    }
}

#endif