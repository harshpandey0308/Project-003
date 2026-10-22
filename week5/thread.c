#include<pthread.h>
#include<stdio.h>
//#include<errno.h>
//#include<unistd.h>
#include<string.h>

void *worker(void *arg){
    printf("hello %d",*(int *)(arg));

    return NULL;
}

int main(){
    printf("thread creation : \n");

    pthread_t worker_;
    int arg = 45;
    int succ_thread = pthread_create(&worker_ , NULL , worker , &arg);

    if(succ_thread == 0){
        pthread_join(worker_ , NULL);
    }
    else if(succ_thread != 0){
        fprintf(stderr , "%s\n" , strerror(succ_thread));
    }

    printf("completed ");
    return 0;
}