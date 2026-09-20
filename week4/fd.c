#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(){
int fd = open("test.txt" , O_RDWR | O_CREAT  , 0644);

if(fd == -1){
    perror("file open failed");
    exit(EXIT_FAILURE);
}

printf("the file descriptor is %d.\n", fd);

lseek(fd , 5 , SEEK_SET);

const char msg[] = "Hello file descriptor.\n";

int success = write(fd , msg , sizeof(msg) - 1);

if(success == -1){
    perror("message sending failed.");
    exit(EXIT_FAILURE);
}

close(fd);

return 0;
}