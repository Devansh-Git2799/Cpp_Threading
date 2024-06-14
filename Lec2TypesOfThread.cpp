#include <bits/stdc++.h>
using namespace std;

// There are 5 ways in which we can implement threads in c++
// 1. Normal Funtions
// 2. Lambda Funtions
// 3. Functors
// 4. Non Static Member functions
// 5. Static member functions
void prints(int x)
{
    cout << "\nX: " << x;
    this_thread::sleep_for(chrono::seconds(3));
}
class Base
{
public:
    // void operator()(int threadId){
    //     cout<<"Thread Id: "<<threadId<<endl;
    // }
    void prints(int x)
    {
        cout << "X: " << x;
    }
    // Stati memeber function
    static void printXAgain(int x)
    {
        cout << "X: " << x;
    }
};
int main()
{

    // Lambda
    // auto fun = [](int threadId){
    //     cout<<"\nThread -> "<<threadId<<endl;
    // };
    // thread t1(fun,1);
    // thread t2((Base()),2);
    // t1.join();
    // t2.join();

    //  Non-Static member Function
    // Base b;
    // thread t1(&Base::prints, &b, 10);
    // t1.join();
    // thread t2(&Base::printXAgain, 10);
    // t2.join();

    // Normal Function
    thread t3(prints, 10);
    thread t2 (prints,11);
    cout<<"mAIN()"<<endl;
    // t3.join();  //.join() function makes the thread programm execution wait until the processing of thread completes , this makes the programm synchronize;
    if(t3.joinable())
    t3.detach();
    // this_thread(chrono(5));
    t2.join();
    cout<<"\nmain after()"<<endl;
}