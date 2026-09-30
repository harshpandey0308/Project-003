#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<signal.h>
#include<sys/types.h>

int main(){
    int status;

    pid_t pid = fork();

    if(pid == 0){
        printf("child pid = %d and parent's pid = %d.\n",getpid() , getppid());

        printf("Parent's pid = %d.\n",getppid());
    }
    else if(pid > 0){
        printf("parent pid = %d.\n",getpid());

        kill(pid , SIGTERM);
        wait(&status);

        if(WIFSIGNALED(status)){
            printf("child exited through signal.\n");
            int st = WTERMSIG(status);
            printf("the actual exit code is %d.\n",st);
        }
        else{
             printf("the status of child process is %d.\n",status);
        }
        
        exit(-1);
    }
    else{
        perror("the chid process is not clear");
        exit(-1);
    }
}