#include<pthread.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>

void *worker(void *arg){
    printf("hello %s",(char *)arg);

    return NULL;
}

int main(){
    printf("thread creation : \n");

    pthread_t worker_;
    int succ_thread = pthread_create(&worker_ , NULL , worker , "Harsh");

    if(succ_thread == 0){
        pthread_join(worker_ , NULL);
    }
    else if(succ_thread != 0){
        strerror(errno);
    }

    printf("completed ");
    return 0;
}