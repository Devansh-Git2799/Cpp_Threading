#include<bits/stdc++.h>
using namespace std;
int main(){
    int result =0;
    auto task = [](int n,int &result){
        result = n*2;
        return result;
    };

    thread t1(task,5,ref(result));
    t1.join();

    cout<<result<<endl;


}