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

    printf("the file descriptor : %d.\n",fd);

    const char msg[12] = "i am home ";

    ssize_t success = write(fd , msg , sizeof(msg) - 1);

    if(success == -1){
        perror("write failed");
        exit(EXIT_FAILURE);
    }

    printf("the total number of bytes of file descriptor %d is %ld.\n" , fd , success);
    
    off_t offset = lseek(fd , 4 , SEEK_SET);

    if(offset == -1){
        perror("offset move failed");
        exit(EXIT_FAILURE);
    }

    off_t offset2 = lseek(fd , 0 , SEEK_CUR);

    if(offset2 == -1){
        perror("offset");
        exit(EXIT_FAILURE);
    }

    printf("the current offset of the file descripttor %d is %ld.\n" , fd  , offset2);

    int fd2 = open("hard.txt" , O_WRONLY | O_CREAT , 0644);

    if(fd2 == -1){
        perror("the second file open failed");
        exit(EXIT_FAILURE);
    }

    printf("the file descriptor second : %d.\n",fd2);

    off_t offset3 = lseek(fd2 , 0 , SEEK_CUR);

    if(offset3 == -1){
        perror("offset 3 failed");
        exit(EXIT_FAILURE);
    }

    printf("the offset of file descriptor %d is %ld.\n" , fd2 , offset3);

    return 0;
}