// Last updated: 2026. 9. 8. 오후 5:13:54
/*
    좌/우 포크 -> 스파게티
*/
#include<mutex>
#include<condition_variable>

class Semaphore{
private:
    int count;
    mutex mtx;
    condition_variable cv;
public:
    Semaphore(int n = 0):count(n){}
    void Set(int n) {count = n;}
    void Signal(){
        std::unique_lock<mutex> lock(mtx);
        count++;
        cv.notify_one();
    }
    void Wait(){
        std::unique_lock<mutex> lock(mtx);
        cv.wait(lock,[&](){
            return count > 0;
        });
        count--;
    }
};

// 최대 식사 접근 인원을 4명으로 제한한다.
// 데드락 방지를 위함임
// P0~P5가 모두 왼쪽 포크를 집는다 생각하자.
// 그러면 오른쪽 포크를 집으려할 때 순환 대기가 발생한다.
// 그러나 4명만 접근 가능하게 하면, 무조건 한 쪽은 비게 되어있다.
class DiningPhilosophers {
private:
    mutex fork_mtx[5]; // fork
    Semaphore eater_semp;
public:
    DiningPhilosophers() {eater_semp.Set(4);}

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
        
        int left = philosopher;
        int right = (philosopher + 1) % 5;

        eater_semp.Wait();
        unique_lock<mutex> lock_left(fork_mtx[left]);
        unique_lock<mutex> lock_right(fork_mtx[right]);

        pickLeftFork();
        pickRightFork();
        eat();
        putLeftFork();
        putRightFork();

        lock_left.unlock();
        lock_right.unlock();

		eater_semp.Signal();
    }
};