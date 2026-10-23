#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<err.h>
//#include<unistd.h>
#include<string.h>

void *worker(void *arg){
    printf("hello %d.\n",*(int *)(arg));

    void *arg2 = malloc(sizeof(int));

    if(arg2 == NULL){
        err(EXIT_FAILURE , "malloc in worker");
    }

    *(int *)arg2 = 2*(*(int *)arg);

    return arg2;
}

int main(){
    printf("thread creation : \n");

    pthread_t worker_;

    void *arg = malloc(sizeof(int));
    if(arg == NULL){
        err(EXIT_FAILURE , "malloc");
    }
    *(int *)arg = 45;
    int succ_thread = pthread_create(&worker_ , NULL , worker , arg);

    if(succ_thread == 0){
        void *arg1 = NULL;
        int join_ = pthread_join(worker_ , &arg1);
        if(join_ != 0){
            printf("join failed");
            exit(EXIT_FAILURE);
        }
        printf("the original value is %d.\n" , *(int *)arg);
        printf("the incremented value is %d.\n",*(int *)arg1);
        free(arg1);
        arg1 = NULL;
    }
    else if(succ_thread != 0){
        fprintf(stderr , "%s\n" , strerror(succ_thread));
    }

    free(arg);
    
    arg = NULL;
    
    printf("completed ");
    return 0;
}