#include<unistd.h>
#include<pthread.h>
#include<stdio.h>
#include<err.h>

void *worker1(void *arg){
    *arg = *arg + 3;

    return arg;
}

int main(){
    
    pthread_t worker_;

    void *arg = malloc(sizeof(int));
    if(arg == NULL){
        err(EXIT_FAILURE , "malloc");
    }

    *arg = 5;

    pthread_t pthread = pthread_create(&worker_ , NULL , worker1 , arg);
}