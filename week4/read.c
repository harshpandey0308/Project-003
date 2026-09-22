#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    int fd = open("har.txt" , O_RDONLY | O_CREAT , 0444);

    if(fd == -1){
        perror("file opening failed");
        exit(EXIT_FAILURE);
    }

    char msg[12];

    ssize_t success = read(fd , msg , 11);

    if(success == -1){
        perror("reading the file failed");
        exit(EXIT_FAILURE);
    }

    msg[success] = '\0';

    printf("the read message is : %s.\n", msg);

    printf("the offset is %ld.\n", success);

    close(fd);
}