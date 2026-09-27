#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
    int fd = open("master.txt" , O_WRONLY | O_CREAT , 0644);

    if(fd == -1){
        perror("file opening failed");
        exit(EXIT_FAILURE);
    }

    int fd2 = open("other.txt" , O_WRONLY | O_CREAT , 0644);
    if(fd2 == -1){
        perror("other file failed");
        exit(EXIT_FAILURE);
    }

    ssize_t ws = write(fd2 , "MASTER" , 7);

    if(ws == -1){
        perror("write failed");
        exit(EXIT_FAILURE);
    }

    int f = dup2(fd , fd2);

    if(f == -1){
        perror("failed");
        exit(EXIT_FAILURE);
    }

    ssize_t ws1 = write(f , "MEssaGew" , 9);

    if(ws1 == -1){
        perror("write   failed");
        exit(EXIT_FAILURE);
    }

    printf("the offset 1 = %ld", lseek(fd , 0 , SEEK_CUR));
    printf("the offset 2 = %ld" , lseek(fd2 , 0 , SEEK_CUR));
    printf("the offset 3 = %ld" , lseek(f , 0 , SEEK_SET));

    close(fd);

    close(fd2);

    return 0;
}