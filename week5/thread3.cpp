#include<iostream>
#include<thread>
#include<chrono>
#include<future>

using namespace std;

int worker_1(int var){
    cout<<"hello i am thread of this program"<<endl;

    var += 50;

    var += 100;

    return var;
    //std::this_thread::sleep_for(std::chrono::seconds(20));

}

int worker_2(int var){
    var = 2*var;

    return var;

}

int worker_3(int var){
    var = 3*var;

    return var;
}

int main(){
    cout<<"creating thread..."<<endl;

    int a = 30;
    int b = 4;
    int c = 5;

    std::future<int>  future1 = std::async(std::launch::async , worker_1 , a);

    std::future<int>  future2 = std::async(std::launch::async , worker_2 , b);

    std::future<int> future3 = std::async(std::launch::async , worker_3 , c);

    cout<<"we are busy"<<endl;
    cout<<"today is sunday"<<endl;
    cout<<"over to u Rajesh"<<endl;
    cout<<"we are getting late"<<endl;

    std::this_thread::sleep_for(std::chrono::seconds(6));

    int result1 = future1.get();

    int result2 = future2.get();

    int result3 = future3.get();

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