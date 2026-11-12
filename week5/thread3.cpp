#include<iostream>
#include<thread>
#include<chrono>

using namespace std;

void worker_thr(){
    cout<<"hello i am thread of this program"<<endl;

    std::this_thread::sleep_for(std::chrono::seconds(20));
}

int main(){
    cout<<"creating thread..."<<endl;

    std::thread worker(worker_thr);

    worker.join();

    cout<<"Thread completion"<<endl;

    return 0;
}