#include<bits/stdc++.h>
using namespace std;
timed_mutex mtx;
int amount=0;

void incrementAmount(int i){
    auto now = chrono::steady_clock::now();  //This is the current time a function from chrono class
    if(mtx.try_lock_for(chrono::seconds(2))){  //this is another way to achieve timed_mutex lock; mtx.try_lock_until(chrono::steady_clock::now() + chrono::seconds(2)
        ++amount;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cout<<"Thread: "<<i<<" go the lock"<<endl;
        mtx.unlock();
    }
    else{
        cout<<"Thread:"<<i<<" didnt get the lock"<<endl;
    }
}
int main()
{
    thread t1(incrementAmount, 1);
    thread t2(incrementAmount,2);

    t1.join();
    t2.join();
    cout<<"Amount: "<<amount;
    return 0;
}


//  any one of the thread will wait till thus 