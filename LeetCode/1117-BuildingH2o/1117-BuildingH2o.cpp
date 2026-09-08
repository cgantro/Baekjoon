// Last updated: 2026. 9. 8. 오후 5:14:01

#include<mutex>
#include<condition_variable>
class H2O {
private:
    // 수소 개수 카운팅하는 공유 변수가 필요할 듯 하다.
    short hyde = 0;
    std::mutex m;
    std::condition_variable cv;
public:
    H2O() = default;

    void hydrogen(function<void()> releaseHydrogen) {
        
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        std::unique_lock<mutex> lock(m); 
        cv.wait(lock,[this](){
            return hyde < 2; // hyde 개수가 2미만이면 된다
        });

        // lock 획득 상태
        releaseHydrogen();
        hyde++;
        lock.unlock();
        cv.notify_all();
    }

    void oxygen(function<void()> releaseOxygen) {
        
        // releaseOxygen() outputs "O". Do not change or remove this line.
        std::unique_lock<mutex> lock(m); 
        cv.wait(lock,[this](){
            return hyde == 2; // hyde 개수가 2면 된다
        });
        releaseOxygen();
        hyde = 0;
        lock.unlock();
        cv.notify_all();
    }
};