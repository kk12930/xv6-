#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define RE 0
#define WR 1

void primes(int* p)
{
    close(p[WR]);
    int n;
    if( read(p[RE],&n,sizeof(int)) != sizeof(int) )
    {
        fprintf(2,"read fail \n");
        exit(1);
    }
    printf("prime %d \n", n);
    
    int p_[2];
    pipe(p_);
    int pid = fork();
    
    if(pid < 0 )
    {
        fprintf(2,"error \n");
        exit(0);
    }else if (pid == 0)
    {
        primes(p_);
    }else {
        close(p_[RE]);
        int sum = n ;
        while(read(p[RE],&n,sizeof(int)))
        {
            if(n % sum != 0 )
            {
                write(p_[WR],&n,sizeof(int));
            }
        }
        close(p_[WR]);
        close(p[RE]);
        wait(0);
    }
    exit(0);

}


int main(int argc,char *argv[])
{
    int p[2];
    pipe(p);
    int fid = fork();

    if(fid < 0 )
    {
        fprintf(2,"error not find fid \n");
        exit(1);
    }else if(fid == 0)
    {
        primes(p);
    }else{

        close(p[RE]);
        
        for(int i =2 ; i< 36 ;i++)
        {
            if(write(p[WR],&i,sizeof(int))!=4)
            {
                fprintf(2,"wait fail \n");
                exit(1);
            }
        }

        close(p[WR]);
        wait(0);
    }
    exit(0);

}