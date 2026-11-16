#include<iostream>
#include<thread>
#include<chrono>
#include<future>

using namespace std;

void worker_1(int& var , std::promise<int> promise){
    cout<<"hello i am thread of this program"<<endl;

    var += 50;

    promise.set_value(var);

    var += 100;

    //std::this_thread::sleep_for(std::chrono::seconds(20));

}

void worker_2(int& var , std::promise<int> promise){
    var = 2*var;

    promise.set_value(var);

}

void worker_3(int& var , std::promise<int> promise){
    var = 3*var;

    promise.set_value(var);
}

int main(){
    cout<<"creating thread..."<<endl;

    int a = 30;
    int b = 4;
    int c = 5;

    std::promise<int> promise;

    std::future<int>  future1 = promise.get_future();

    std::promise<int> promise2;

    std::future<int>  future2 = promise2.get_future();

    std::promise<int> promise3;

    std::future<int> future3 = promise3.get_future();

    std::thread worker_(worker_1 , std::ref(a) , std::move(promise));

    cout<<"we are busy"<<endl;
    cout<<"today is sunday"<<endl;
    cout<<"over to u Rajesh"<<endl;

    std::thread worker2(worker_2 , std::ref(b) , std::move(promise2));

    cout<<"we are getting late"<<endl;
    
   //std::this_thread::sleep_for(std::chrono::seconds(5));

    std::thread worker3(worker_3 , std::ref(c) , std::move(promise3));

    std::this_thread::sleep_for(std::chrono::seconds(6));

    int result1 = future1.get();

    int result2 = future2.get();

    int result3 = future3.get();

    worker_.join();

    worker2.join();

    worker3.join();

    //cout<<"variable : "<<a<<endl;

    
    //cout<<worker.joinable()<<endl;

    cout<<"sum value : "<<result1<<endl;

     cout<<"2 multiple : "<<result2<<endl;

     cout<<"3 multiple : "<<result3<<endl;
    //

    //std::terminate();

    //worker.terminate();

    cout<<"Thread completion"<<endl;

    return 0;
}