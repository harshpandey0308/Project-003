#include<iostream>
#include<mutex>
#include<thread>

#define LOOP_TIME 1000000

using namespace std;

void worker_a(int& value , std::mutex& mutex_){
    std::unique_lock<std::mutex> guard(mutex_);
    
    value = value + 40;

    cout<<"value : "<<value;

    guard.unlock();

    int sum = 0;

    for(size_t i=0 ; i<100 ; i++){
       sum = sum + i;
    }

    guard.lock();

    cout<<"value :"<<value<<endl;
    
    guard.unlock();
    
}

void worker_b(int& value , std::mutex& mutex){
    std::lock_guard<std::mutex> guard(mutex);

    for(int i=0 ; i<5 ; i++){
        value = value + 10;
        //value = value/0;
    }
}

int main(){
    int a = 5;

    std::mutex mtx;

    std::thread worker1(worker_a , std::ref(a) , std::ref(mtx));

    std::thread worker2(worker_b , std::ref(a) , std::ref(mtx));

    worker1.join();

    //cout<<"the value of a is "<<endl;

    worker2.join();

    cout<<"the value of a is "<<a<<endl;

}