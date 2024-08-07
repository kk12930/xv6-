
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc,char *argv[])
{
    if(argc != 2) {
        fprintf(2,"input_validation_error_message \n");
        exit(0);
    }else {
        int n = atoi(argv[1]);
        sleep(n);
        exit(0);
    }
    exit(0);

}