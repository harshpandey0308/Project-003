#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
    int fd = open("har.txt" , O_WRONLY | O_CREAT , 0666);

    if(fd == -1){
        perror("file opening failed");
        exit(EXIT_FAILURE);
    }

    const char msg[13] = "Hello Harsh";

    off_t set1 = lseek(fd , 0 , SEEK_SET);

    printf("the offset is at position %ld\n",set1);

    ssize_t wr_success = write(fd , msg , sizeof(msg) - 1);

    if(wr_success == -1){
        perror("message writing failed");
        exit(EXIT_FAILURE);
    }

    close(fd);


return 0;
}