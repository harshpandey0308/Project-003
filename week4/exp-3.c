#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
    int fd = open("HARS.txt" , O_RDWR | O_CREAT , 0664);

    if(fd == -1){
        perror("file opening failed");
        exit(EXIT_FAILURE);
    }

    printf("the file descriptor is %d.\n",fd);

    pid_t new_pid = fork();

    if(new_pid == 0){
        printf("the pid of child process = %d and the pid of parent process is %d.\n" , getpid() , getppid());
        printf("the fd of process %d is %d.\n" , getpid() , fd);

        off_t child_off = lseek(fd , 5  , SEEK_SET);
        if(child_off == -1){
            perror("offset failed");
            exit(EXIT_FAILURE);
        }
        printf("the offset of the child process : %ld.\n" , lseek(fd , 0 , SEEK_CUR));

        char msg[6] = "child";
        ssize_t ws = write(fd , msg , sizeof(msg) - 1);

        if(ws == -1){
            perror("the write failed");
            exit(EXIT_FAILURE);
        }

        printf("the offset of the child process : %ld.\n" , lseek(fd , 0 , SEEK_CUR));
        
    }
    else if(new_pid > 0){
        printf("the fd of process %d is %d.\n",getpid() , fd);

        wait(NULL);

        const char msg1[7] = "Parent";
        ssize_t ws1 = write(fd , msg1 , sizeof(msg1) - 1);

        if(ws1 == -1){
            perror("writing failed");
            exit(EXIT_FAILURE);
        }
        printf("the offset of the parent process is %ld.\n", lseek(fd , 0 , SEEK_CUR));
    }
    else{
        perror("failed");
        exit(EXIT_FAILURE);
    }

     return 0;
}