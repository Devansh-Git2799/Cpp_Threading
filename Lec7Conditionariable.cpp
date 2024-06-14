//IMPORTANT POINT: CV are used for two purpose
// A. Notify other threads
// B. Waiting for some conditions
// 1. Condition Variable allows running threads to wait on some conditions and once those conditions are met the waiting thread
// is notified using :
// a. notify_one();
// b. notify_all();
// 2. You need mutex to use condition variable.
// 3. If some thread want to wait on some condition then it has to do these things:
// a. Acquire the mutex lock using std::unique_lock<std::mutex> lock (m);.
// b. Execute wait, wait_for, or wait until. The wait operations atomically release the mutex
// and suspend the execution of the thread.
// c. When the condition variable is notified, the thread is awakened, and the mutex is atomically reacquired.
// The thread should then check the condition and resume waiting if the wake up was spurious.
// NOTE:
// 1. Condition variables are used to synchronize two or more threads.
// 2. Best use case of condition variable is Producer/Consumer problem.


#include <iostream>
#include <thread>
#include <condition_variable>
using namespace std;

condition_variable cv;
int balance = 0;
mutex m;
void addMoney(string threadId, int amount)
{
    balance += amount;
    cout << "\nbalance added by threadId: " << threadId << balance << endl;
    cv.notify_all();
}
void withDrawMoney(string threadId, int amount)
{
    unique_lock<mutex> ul(m); /// Say some thread has acquitred the lock m has ownership of the lock
    cv.wait(ul, []
            { return (balance != 0) ? true : false; }); // based on the condition variable the release of the lock will happen when the predicate returns true then unique_lock will acquire the lock else it will wait for the cv to notifiy , if cv notifies it then again it will check the condition.
    if (balance >= amount)
    {
        balance -= amount;
        cout << "\nbalance after widthdrawl by threadId: " << threadId << balance << endl;
    }
    else
    {
        cout << "balance is not deducted by threadId: " << threadId << " " << balance << endl;
    }
}

int main()
{
    thread t1(withDrawMoney, "T1 ", 600);
    thread t2(addMoney, "T2 ", 500);
    t1.join();
    t2.join();
    return 0;
}