// NOTES:
// 0. It is same as mutex but, Same thread can lock one mutex multiple times using recursive_mutex.
// 1. If thread T1 first call lock/try_lock on recursive mutex m1, then ml is locked by T1, now as T1 is running in recursion, T1 can call lock/try_lock any number of times there is no issue.
// 2. But if T1 have aquired 10 times lock/try_lock on mutex m1 then thread T1 will have to unlock it 10 times otherwise no other thread will be able to lock mutex m1. It means recursive_mutex keeps count how many times it was locked so that many times it should be unlocked.
// 3. There is no such limit on calling the reursive _mutex but if system had enought of the overheades then if we call lock() after that threshold(not defined here ) it will return std::system_error OR if we were calling try_lock() then it will return false.

// BOTTOM LINE:
// 0. It is similar to mutex but have extra facitility that it can be locked multiple time by same thread.
// 1. If we can avoid recursive_mutex then we should becuase it brings overhead to the system.
// 2. It can be used in loops also.

#include<bits/stdc++.h>
using namespace std;
int buff = 0;
recursive_mutex mtx;   //if recursive_mutex is locked by n no times then  n no of times this is needed to be unlocked

void recursiveFun(char c,int loopFor){
    if(loopFor<0){
        return;
    }
    mtx.lock();
    cout<<"Thread Id:"<<c<<" Locked "<<buff++<<endl;
    recursiveFun(c,--loopFor);
    mtx.unlock();
    cout<<"Thread Id:"<<c<<" Unlocked "<<endl;
}

int main()
{
    thread t1(recursiveFun,'1',2);
    thread t2(recursiveFun,'2',2);
    t1.join();
    t2.join();
    return 0;
}