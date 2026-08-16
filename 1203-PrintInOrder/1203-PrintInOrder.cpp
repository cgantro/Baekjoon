// Last updated: 2026. 8. 16. 오후 2:12:09
#include<functional>
#include<mutex>
#include<condition_variable>
class Foo {
private:
        std::mutex m;
        std::condition_variable cv;
        short turn = 0;
public:
    Foo() {
    }

    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        {
            std::lock_guard<std::mutex> lock(m);
        }
        turn = 2;
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        
        // printSecond() outputs "second". Do not change or remove this line.
        std::unique_lock<mutex> lock(m);
        cv.wait(lock, [this](){return turn == 2;});
        printSecond();
        turn = 3;
        cv.notify_all();
    }

    void third(function<void()> printThird) {
        
        // printThird() outputs "third". Do not change or remove this line.
        std::unique_lock<mutex> lock(m);
        cv.wait(lock, [this](){return turn == 3;});
        printThird();
        
        cv.notify_all();
    }
};