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

    char msg[20];

    ssize_t success = read(fd , msg , 15);

    if(success == -1){
        perror("reading the file failed");
        exit(EXIT_FAILURE);
    }

    off_t offset1 = lseek(fd , 0 , SEEK_CUR);

    if(offset1 == -1){
        perror("the offset failed");
        exit(-1);
    }

    printf("the file offset is %ld.\n" , offset1);

    msg[success] = '\0';

    printf("the read message is : %s.\n", msg);

    printf("the number of bytes read  is %ld.\n", success);

    ssize_t success1 = read(fd , msg , 20);

    if(success1 == -1){
        perror("second reading failed");
        exit(-1);
    }

    msg[offset1] = '\0';

    off_t offset = lseek(fd , 0 , SEEK_CUR);

    if(offset == -1){
        perror("the offset failed");
        exit(-1);
    }

    printf("the file offset is %ld.\n" , offset);

    printf("read message : %s\n" , msg);

    printf("the number bytes read is %ld\n",success1);

    close(fd);
}