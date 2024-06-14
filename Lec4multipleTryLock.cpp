#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

int X = 0, Y = 0;
std::mutex m1, m2;

void doSomeWorkForSeconds(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void incrementXY(int& XorY, std::mutex& m, const char* desc) {
    for (int i = 0; i < 5; ++i) {
        m.lock();
        ++XorY;
        cout << desc << XorY << '\n';
        m.unlock();
        doSomeWorkForSeconds(1);
    }
}

void consumeXY() {
    int useCount = 5;
    int XplusY = 0;

    while (useCount > 0) {
        // Attempt to lock both mutexes m1 and m2
        int lockResult = std::try_lock(m1, m2);

        if (lockResult == -1) { // Successfully locked both mutexes
            if (X != 0 && Y != 0) {
                --useCount;
                XplusY += X + Y;
                X = 0;
                Y = 0;
                cout << "XplusY: " << XplusY << '\n';
            }
            m1.unlock();
            m2.unlock();
        }

        // Wait or do other work while waiting for another iteration
        doSomeWorkForSeconds(1);
    }
}

int main() {
    std::thread t1(incrementXY, std::ref(X), std::ref(m1), "X: ");
    std::thread t2(incrementXY, std::ref(Y), std::ref(m2), "Y: ");
    std::thread t3(consumeXY);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}


// here what is happening is thread t3 is using try_lock(m1,m2,m3,m4,...,mn) try to lock multiple mutexes at the same time if it is able to lock mutexs it return -1 else visualise the m1 m2 m3 as o based indexes and return that index for eg m3 is not locked then it will return 2 => m3 is not locked so it will unlock all if it succeds we can access X and Y re initalize and go on working. 