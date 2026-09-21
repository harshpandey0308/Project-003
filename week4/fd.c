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

off_t set = lseek(fd , 0 , SEEK_SET);

if(set == -1){
    perror("setting offset failed");
    exit(EXIT_FAILURE);
}
const char msg[] = "Hello file descriptor.\n";

int success = write(fd , msg , sizeof(msg) - 1);

if(success == -1){
    perror("message sending failed.");
    exit(EXIT_FAILURE);
}

off_t cur = lseek(fd , 3 , SEEK_CUR);

if(cur == -1){
    perror("moving current offset failed");
    exit(EXIT_FAILURE);
}

const char msg2[] = "after moving 3 steps far from the word Hello.";

int success1 = write(fd , msg2 , sizeof(msg2) - 1);

if(success1 == -1){
    perror("moving offset failed");
    exit(EXIT_FAILURE);
}

off_t end = lseek(fd , -4 , SEEK_END);

if(end == -1){
    perror("moving offset from the EOF is failed");
    exit(EXIT_FAILURE);
}

const char msg3[] = "I am OPTIMUS PRIME and I am calling all autobots who are refugee in the multiple planet of this galaxy.";

int success3 = write(fd , msg3 , sizeof(msg3) - 1);

if(success3 == -1){
    perror("seek end failed");
    exit(EXIT_FAILURE);
}

off_t size = lseek(fd , 0 , SEEK_END);

if(size == -1){
    perror("size failed");
    exit(EXIT_FAILURE);
}

printf("the file size is %ld", size);

close(fd);

return 0;
}