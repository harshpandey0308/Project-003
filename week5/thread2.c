#include<unistd.h>
#include<pthread.h>
#include<stdio.h>
#include<err.h>
#include<stdlib.h>

typedef struct Box{
    int *sha_counter;
    pthread_mutex_t *mutex_;
}Box;

void *worker1(void *arg){
    Box *b_arg = (Box *)arg;

    int lock = pthread_mutex_lock(b_arg->mutex_);
    if(lock != 0){
        err(EXIT_FAILURE , "LOck");
    }

    *(b_arg->sha_counter) = *(b_arg->sha_counter) + 1;

    int unlock = pthread_mutex_unlock(b_arg->mutex_);
    if(unlock != 0){
        err(EXIT_FAILURE , "unlock");
    }

    return (void *)b_arg;
}

void *worker_2(void *arg){
    Box *b = (Box *)arg;

    int lock1 = pthread_mutex_lock(b->mutex_);
    if(lock1 != 0){
        err(EXIT_FAILURE , "lock1");
    }

    *(b->sha_counter) = *(b->sha_counter) - 1;

    int unlock = pthread_mutex_unlock(b->mutex_);
    if(unlock != 0){
        err(EXIT_FAILURE , "unlock");
    }

    return (void *)b;
}

int main(){
    Box b1;

    int shared_counter = 0;
    pthread_mutex_t mutex;

    b1.sha_counter = &shared_counter;
    b1.mutex_ = &mutex;

    int init = pthread_mutex_init(b1.mutex_ , NULL);
    
    pthread_t worker_;

    Box *arg = &b1;

    int pthread = pthread_create(&worker_ , NULL , worker1 , (void *)arg);
    if(pthread == 0){
        pthread_t worker2;
        int pthread2 = pthread_create(&worker2 , NULL , worker_2 , (void *)arg);
        if(pthread2 == 0){
            void *arg2 = NULL;
            int join_ = pthread_join(worker2 , &arg2);

            if(join_ != 0){
                err(EXIT_FAILURE , "join");
            }
        }


        void *arg1 = NULL;
        int join = pthread_join(worker_ , &arg1);

        if(join != 0){
            err(EXIT_FAILURE , "join");
        }
        
        printf("The shared counter is %d.\n",*(((Box *)arg1)->sha_counter));
    }

    int destroy = pthread_mutex_destroy(b1.mutex_);
    if(destroy != 0){
        err(EXIT_FAILURE , "destroy");
    }

    return 0;
}