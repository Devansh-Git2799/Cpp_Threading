// TOPIC: lock_guard In C++ (std::lock_guard<mutex> lock (m1))
// NOTES:
// 0. It is very light weight wrapper for owning mutex on scoped basis.
// 1. It aquires mutex lock the moment you create the object of lock_guard.
// 2. It automatically removes the lock while goes out of scope.
// 3. You can not explicitly unlock the lock_guard. as it is on the scope basis
// 4. You can not copy lock_guard.

#include <bits/stdc++.h>
#include <thread>
using namespace std;
mutex mtx;
int x=0;
void sharedResources(int threadId)
{
    // this is the one way to lock the mutex so that at a time only one thread access the shared resource;
    // mtx.lock();
    //lock_guard<mutex> locks(mtx); // lock_guard is the template class of type mutex and lock is object which take mutex as argument so when the scope of the lock obj gets over then automaticallu the destructor unlocks it so no need to explicitly mention for unlock
    lock_guard<mutex> lock(mtx);
    cout << "\nThreadId:"<<threadId<<" and value of x is:"<<++x<<endl;
    // mtx.unlock();
}
int main()
{
    thread t1(sharedResources,1);
    thread t2(sharedResources,2);

    t1.join();
    t2.join(); // It is used to join threads with main thread
}
