#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>

int main(){

    int fd = open("har.txt" , O_WRONLY | O_CREAT , 0644);

    if(fd == -1){
        perror("file open failed");
        exit(EXIT_FAILURE);
    }

    int fd2 = dup(fd);

    if(fd2 == -1){
        perror("the second file open failed");
        exit(EXIT_FAILURE);
    }

    printf("the file descriptor : %d.\n",fd);

    const char msg[12] = "i am home ";

    ssize_t success = write(fd , msg , sizeof(msg) - 1);

    if(success == -1){
        perror("write failed");
        exit(EXIT_FAILURE);
    }

    printf("the current offset of the file descriptor %d is %ld.\n",fd , lseek(fd , 0 , SEEK_CUR));
    printf("the current offset of the file descripttor %d is %ld.\n" , fd2  , lseek(fd2 , 0 , SEEK_CUR));

    printf("the total number of bytes of file descriptor %d is %ld.\n" , fd , success);
    
    off_t offset = lseek(fd , 2 , SEEK_SET);

    if(offset == -1){
        perror("offset move failed");
        exit(EXIT_FAILURE);
    }

    printf("first file descriptor : %d.\n",fd);
    printf("the file descriptor second : %d.\n",fd2);

    printf("the current offset of the file descriptor %d is %ld.\n",fd , lseek(fd , 0 , SEEK_CUR));
    printf("the current offset of the file descripttor %d is %ld.\n" , fd2  , lseek(fd2 , 0 , SEEK_CUR));

    
    return 0;
}