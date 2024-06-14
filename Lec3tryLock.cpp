#include <bits/stdc++.h>
using namespace std;

int counter = 0;
mutex mtx;
void incrementCounter(int threadId){
    for(int i=0;i<1000;i++){
        if(mtx.try_lock()){
            ++counter;
            mtx.unlock();
        }
        else{
            cout<<"Thread"<<threadId<<" didnt get the mutex lock"<<endl;
        }
    }
}
int main()
{
    thread t1(incrementCounter, 1);
    thread t2(incrementCounter,2);
    t1.join();
    t2.join();
    cout<<"Value of Counter: "<<counter<<endl;
}