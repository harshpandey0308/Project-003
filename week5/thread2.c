#include<unistd.h>
#include<pthread.h>
#include<stdio.h>
#include<err.h>
#include<stdlib.h>

#define ITR 10000000

typedef struct Box{
    int *sha_counter;
    int *buffer_empty;
    pthread_mutex_t *mutex_;
    pthread_mutex_t *output_mutex;
    pthread_cond_t *not_empty;
    pthread_cond_t *not_full;
}Box;

void *producer(void *arg){
    Box *b_arg = (Box *)arg;

    for(int i=0 ; i<5 ; i++){

        int lock_mutex = pthread_mutex_lock(b_arg->output_mutex);
        if(lock_mutex != 0){
            err(EXIT_FAILURE , "output_mutex");
        }

        printf("enter the new value:");
        
        int unlock_mutex = pthread_mutex_unlock(b_arg->output_mutex);
        if(unlock_mutex != 0){
            err(EXIT_FAILURE , "mutex unlock");
        }

        int val;
        if(scanf("%d",&val) != 1){
            printf("invalid data , enter the valid data(integer)");
            return NULL;
        }
        else{
            printf("the data is valid\n");
        }

        int lock = pthread_mutex_lock(b_arg->mutex_);
        if(lock != 0){
            err(EXIT_FAILURE , "LOck");
        }

        while(!*(b_arg->buffer_empty)){
            pthread_cond_wait(b_arg->not_full , b_arg->mutex_);
        }
        
        
        *(b_arg->sha_counter) = val;

        *(b_arg->buffer_empty) = 0;

        pthread_cond_signal(b_arg->not_empty);
        
        int unlock = pthread_mutex_unlock(b_arg->mutex_);
        if(unlock != 0){
            err(EXIT_FAILURE , "unlock");
        }
    }

    return NULL;
}

void *consumer(void *arg){
    Box *b = (Box *)arg;

    int msg_rcv;

    for(int i=0 ; i<5 ; i++){
        int lock1 = pthread_mutex_lock(b->mutex_);
        if(lock1 != 0){
            err(EXIT_FAILURE , "lock1");
        }

        while(*(b->buffer_empty)){
            pthread_cond_wait(b->not_empty , b->mutex_);
        }

        msg_rcv = *(b->sha_counter);

        *(b->buffer_empty) = 1;

        pthread_cond_signal(b->not_full);
        
        int unlock = pthread_mutex_unlock(b->mutex_);
        if(unlock != 0){
            err(EXIT_FAILURE , "unlock");
        }

        int out_mutex = pthread_mutex_lock(b->output_mutex);
        if(out_mutex != 0){
            err(EXIT_FAILURE , "Lock output failed");
        }

        printf("message received : %d.\n",msg_rcv);

        int unlock_out = pthread_mutex_unlock(b->output_mutex);
        if(unlock_out != 0){
            err(EXIT_FAILURE , "unlock output failed");
        }
    }

    return NULL;
}

int main(){
    Box b1;

    int shared_counter = 0;
    int is_buffer_empty = 1;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
    pthread_mutex_t op_mutex;

    b1.sha_counter = &shared_counter;
    b1.mutex_ = &mutex;
    b1.buffer_empty = &is_buffer_empty;
    b1.not_empty = &not_empty;
    b1.not_full = &not_full;
    b1.output_mutex = &op_mutex;

    int init = pthread_mutex_init(b1.mutex_ , NULL);
    if(init != 0){
        err(EXIT_FAILURE , "initialization failed");
        exit(EXIT_FAILURE);
    }

    int init_op_mutex = pthread_mutex_init(b1.output_mutex , NULL);
    if(init_op_mutex != 0){
        err(EXIT_FAILURE , "initialization failed");
        exit(EXIT_FAILURE);
    }

    int init_cond = pthread_cond_init(b1.not_empty , NULL);
    if(init_cond != 0){
        err(EXIT_FAILURE , "pthread condition");
        exit(EXIT_FAILURE);
    }

    int init_cond2 = pthread_cond_init(b1.not_full , NULL);
    if(init_cond2 != 0){
       err(EXIT_FAILURE , "pthread condition second");
       exit(EXIT_FAILURE);
    }
    
    pthread_t worker_;

    Box *arg = &b1;

    int pthread = pthread_create(&worker_ , NULL , producer , (void *)arg);
    if(pthread == 0){
        pthread_t worker2;
        int pthread2 = pthread_create(&worker2 , NULL , consumer , (void *)arg);
        if(pthread2 == 0){
            int join_ = pthread_join(worker2 , NULL);

            if(join_ != 0){
                err(EXIT_FAILURE , "join");
            }
        }
        else{
            printf("second thread creation failed");
            exit(EXIT_FAILURE);
        }

        int join = pthread_join(worker_ , NULL);

        if(join != 0){
            err(EXIT_FAILURE , "join");
        }
        
        printf("The shared counter is %d.\n", *(b1.sha_counter));
    }
    else{
        err(EXIT_FAILURE , "thread creation fails");
    }

    int destroy_cond = pthread_cond_destroy(b1.not_empty);
    if(destroy_cond != 0){
        err(EXIT_FAILURE , "destroy cond variable");
    }

    int destroy_cond2 = pthread_cond_destroy(b1.not_full);
    if(destroy_cond2 != 0){
        err(EXIT_FAILURE , "destroy cond variable");
    }

    int destroy = pthread_mutex_destroy(b1.mutex_);
    if(destroy != 0){
        err(EXIT_FAILURE , "destroy");
    }

    return 0;
}