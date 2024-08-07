#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define RE 0
#define WR 1
 
int main(int argc,char *argv[])
{
    int p_f_z[2];
    int p_z_f[2];
    pipe(p_f_z);
    pipe(p_z_f);
    char buf[1] = "x";
    int pid = fork();
    if(fork < 0 ){
        fprintf(2,"child_process_creation_error\n");
        exit(0);
    }else if(pid == 0)
    {
        close(p_f_z[WR]);
        close(p_z_f[RE]);
        if(read(p_f_z[RE],buf,1))
        {
            printf("%d: received ping\n",pid);
            write(p_z_f[WR],buf,1);
        }else fprintf(2,"not find ping sign\n");
        close(p_f_z[WR]);
        close(p_z_f[RE]);
        exit(0);

    }else {
        close(p_f_z[RE]);
        close(p_z_f[WR]);
        write(p_f_z[WR],buf,1);
        if(read(p_z_f[RE],buf,1))
        {
            printf("%d: received pong\n",pid);
            
        }else fprintf(2,"not find pong sign\n");
        close(p_f_z[WR]);
        close(p_z_f[RE]);
        exit(0);
    }


    exit(0);
}